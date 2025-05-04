using System.ComponentModel.DataAnnotations.Schema;
namespace CommentApi.Models;

public class LogEntry
{
    [Column("id")]
    public int Id { get; set; }

    [Column("timestamp")]
    public DateTime Timestamp { get; set; }

    [Column("level")]
    public string Level { get; set; } = string.Empty;
    [Column("message")]
    public string Message { get; set; } = string.Empty;

    [Column("exception")]
    public string? Exception { get; set; }

    [Column("source")]
    public string? Source { get; set; }

    [Column("request_path")]
    public string? RequestPath { get; set; }

    [Column("user_id")]
    public string? UserId { get; set; }

    [Column("trace_id")]
    public string? TraceId { get; set; }

    [Column("span_id")]
    public string? SpanId { get; set; }
}