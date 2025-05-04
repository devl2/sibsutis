using Microsoft.EntityFrameworkCore;
using CommentApi.Models;
using Microsoft.Extensions.Logging.Abstractions;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
    {
        Database.EnsureCreated();
    }

    public DbSet<Comment> Comment { get; set; }
    public DbSet<LogEntry> Logs { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Comment>().ToTable("Comment");
        modelBuilder.Entity<Comment>(entity =>
        {
            entity.Property(e => e.Id);
            entity.Property(e => e.Name).HasColumnName("Name").IsRequired().HasMaxLength(100);
            entity.Property(e => e.Email).HasColumnName("Email").IsRequired().HasMaxLength(100);
            entity.Property(e => e.Body).HasColumnName("Body").IsRequired();
            entity.Property(e => e.PostId).HasColumnName("PostId").IsRequired();
        });

        modelBuilder.Entity<LogEntry>().ToTable("Logs");
        modelBuilder.Entity<LogEntry>(entity =>
        {
            entity.Property(e => e.Id);
            entity.Property(e => e.Timestamp).IsRequired();
            entity.Property(e => e.Level).IsRequired().HasMaxLength(10);
            entity.Property(e => e.Message).IsRequired();
            entity.Property(e => e.Exception);
            entity.Property(e => e.Source).HasMaxLength(255);
            entity.Property(e => e.RequestPath).HasMaxLength(255);
            entity.Property(e => e.UserId).HasMaxLength(255);
            entity.Property(e => e.TraceId).HasMaxLength(50);
            entity.Property(e => e.SpanId).HasMaxLength(50);
        });
    }

    public async Task DropCommentTable()
    {
        await Database.ExecuteSqlRawAsync("DROP TABLE IF EXISTS \"Comment\" CASCADE");
    }

    public async Task DropLogsTable()
    {
        await Database.ExecuteSqlRawAsync("DROP TABLE IF EXISTS \"Logs\" CASCADE");
    }
}