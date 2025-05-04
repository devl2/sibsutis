using Microsoft.Extensions.Logging;
using System;
using System.Collections.Concurrent;
using Microsoft.EntityFrameworkCore;

public class DatabaseLoggerProvider : ILoggerProvider
{
    private readonly IServiceProvider _serviceProvider;
    private readonly ConcurrentDictionary<string, DatabaseLogger> _loggers = new();

    public DatabaseLoggerProvider(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
    }

    public ILogger CreateLogger(string categoryName)
    {
        return _loggers.GetOrAdd(categoryName, name => new DatabaseLogger(name, _serviceProvider));
    }

    public void Dispose()
    {
        _loggers.Clear();
        GC.SuppressFinalize(this);
    }
}