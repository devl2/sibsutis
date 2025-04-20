using System.Text.Json;
using CommentApi.Controllers;
using CommentApi.Repositories;
using CommentApi.Services;
using Microsoft.AspNetCore.Mvc;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddSingleton<ICommentRepository, CommentRepository>();
builder.Services.AddScoped<CommentService>();

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

app.UseCors("AllowAll");
app.UseRouting();
app.MapCommentsRoutes();

app.MapGet("/test", () => Results.Json(new { message = "Server is working!" }));
app.MapGet("/test-comments", (CommentService service) =>
{
    return Results.Ok(service.GetAll());
});
app.MapPatch("/test-comments/{id}", (int id, [FromBody] Dictionary<string, object> patch, CommentService service) =>
{
    Console.WriteLine($"Received PATCH for id {id}: {JsonSerializer.Serialize(patch)}");
    var result = service.PartialUpdate(id, patch);
    return result is not null
        ? Results.Ok(result)
        : Results.NotFound($"Comment with id {id} not found");
});

app.Run();