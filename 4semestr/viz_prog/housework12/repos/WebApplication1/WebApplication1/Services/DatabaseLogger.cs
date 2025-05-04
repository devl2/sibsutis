using Microsoft.Extensions.Logging;
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Http;
using CommentApi.Models;

public class DatabaseLogger : ILogger
{
    private readonly string _categoryName;
    private readonly IServiceProvider _serviceProvider;

    public DatabaseLogger(string categoryName, IServiceProvider serviceProvider)
    {
        _categoryName = categoryName;
        _serviceProvider = serviceProvider;
    }

    public IDisposable BeginScope<TState>(TState state) => null;

    public bool IsEnabled(LogLevel logLevel) => logLevel >= LogLevel.Information;

    public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception exception, Func<TState, Exception, string> formatter)
    {
        if (!IsEnabled(logLevel))
            return;

        var message = formatter(state, exception);
        var exceptionString = exception?.ToString();

        try
        {
            using var scope = _serviceProvider.CreateScope();
            var context = scope.ServiceProvider.GetRequiredService<AppDbContext>();
            var httpContextAccessor = scope.ServiceProvider.GetService<IHttpContextAccessor>();

            var logEntry = new LogEntry
            {
                Timestamp = DateTime.UtcNow,
                Level = logLevel.ToString(),
                Message = message,
                Exception = exceptionString,
                Source = _categoryName,
                RequestPath = httpContextAccessor?.HttpContext?.Request.Path,
                UserId = httpContextAccessor?.HttpContext?.User.Identity?.Name
            };

            context.Logs.Add(logEntry);
            context.SaveChanges();
            Console.WriteLine($"Log saved: {logEntry.Message}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Failed to write log to database: {ex.Message}");
            if (ex.InnerException != null)
            {
                Console.WriteLine($"Inner exception: {ex.InnerException.Message}");
            }
        }
    }
}