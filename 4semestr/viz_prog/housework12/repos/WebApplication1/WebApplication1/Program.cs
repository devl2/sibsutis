using System.Text.Json;
using CommentApi.Controllers;
using CommentApi.Models;
using CommentApi.Repositories;
using CommentApi.Services;
using Microsoft.AspNetCore.HttpLogging;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

builder.Configuration.AddJsonFile("appsettings.json", optional: false, reloadOnChange: true);

var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
if (string.IsNullOrEmpty(connectionString))
{
    throw new InvalidOperationException("Connection string 'DefaultConnection' not found in configuration");
}

builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseNpgsql(connectionString));

builder.Services.AddScoped<ICommentRepository, CommentRepository>();
builder.Services.AddScoped<CommentService>();

builder.Logging.ClearProviders();
builder.Logging.AddConsole();
builder.Logging.AddDebug();
builder.Logging.AddProvider(new DatabaseLoggerProvider(builder.Services.BuildServiceProvider()));

builder.Services.AddHttpLogging(logging =>
{
    logging.LoggingFields = HttpLoggingFields.All;
    logging.RequestBodyLogLimit = 4096;
    logging.ResponseBodyLogLimit = 4096;
});

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowAll", policy =>
    {
        policy.WithOrigins("http://localhost:3000", "https://localhost:3000")
              .AllowAnyMethod()
              .AllowAnyHeader();
    });
});

var app = builder.Build();

try
{
    using var scope = app.Services.CreateScope();
    var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
    if (await db.Database.CanConnectAsync())
    {
        Console.WriteLine("Database connection successful");
    }
    else
    {
        Console.WriteLine("Failed to connect to database");
    }
}
catch (Exception ex)
{
    Console.WriteLine($"Database connection error: {ex.Message}");
    throw;
}

app.UseHttpLogging();
app.UseCors("AllowAll");
app.UseRouting();

app.MapCommentsRoutes();

app.MapGet("/test", () => Results.Json(new { message = "Server is working!" }));

app.MapGet("/test-comments", async (CommentService service) =>
{
    return Results.Ok(await service.GetAll());
});

app.MapPatch("/test-comments/{id}", async (int id, [FromBody] Dictionary<string, object> patch, CommentService service) =>
{
    Console.WriteLine($"Received PATCH for id {id}: {JsonSerializer.Serialize(patch)}");
    var result = await service.PartialUpdate(id, patch);
    return result is not null
        ? Results.Ok(result)
        : Results.NotFound($"Comment with id {id} not found");
});

app.MapGet("/test-logging", async (ILogger<Program> logger, AppDbContext dbContext) =>
{
    logger.LogInformation("Test information message");
    logger.LogWarning("Test warning message");
    logger.LogError("Test error message");

    try
    {
        var logsCount = await dbContext.Logs.CountAsync();
        return Results.Ok(new
        {
            Message = "Test logs written",
            StoredLogsCount = logsCount
        });
    }
    catch (Exception ex)
    {
        return Results.Problem($"Failed to count logs: {ex.Message}");
    }
});

app.MapGet("/api/logs/debug", async (
    AppDbContext context,
    [FromQuery] int page = 1,
    [FromQuery] int pageSize = 10,
    [FromQuery] string? level = null,
    [FromQuery] string? source = null,
    [FromQuery] string? search = null,
    [FromQuery] DateTime? fromDate = null,
    [FromQuery] DateTime? toDate = null
) =>
{
    try
    {
        var query = context.Logs.AsQueryable();

        if (!string.IsNullOrEmpty(level))
        {
            query = query.Where(l => l.Level == level);
        }

        if (!string.IsNullOrEmpty(source))
        {
            query = query.Where(l => l.Source != null && l.Source.Contains(source));
        }

        if (!string.IsNullOrEmpty(search))
        {
            query = query.Where(l => l.Message.Contains(search));
        }

        if (fromDate.HasValue)
        {
            query = query.Where(l => l.Timestamp >= fromDate);
        }
        if (toDate.HasValue)
        {
            query = query.Where(l => l.Timestamp <= toDate);
        }

        var totalCount = await query.CountAsync();
        var logs = await query
            .OrderByDescending(l => l.Timestamp)
            .Skip((page - 1) * pageSize)
            .Take(pageSize)
            .ToListAsync();

        return Results.Ok(new
        {
            Success = true,
            Logs = logs,
            Count = totalCount,
            Page = page,
            PageSize = pageSize
        });
    }
    catch (Exception ex)
    {
        return Results.Problem($"Error: {ex.Message}");
    }
});

app.Run();