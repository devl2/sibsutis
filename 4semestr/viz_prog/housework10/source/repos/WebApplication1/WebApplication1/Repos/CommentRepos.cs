using System.Reflection;
using System.Text.Json;
using CommentApi.Models;

namespace CommentApi.Repositories;

public class CommentRepository : ICommentRepository
{
    private readonly Dictionary<int, Comment> _comments = new();
    private int _nextId = 1;

    public CommentRepository()
    {
        Add(new Comment
        {
            Id = 1,
            Name = "Test User 1",
            Email = "user1@test.com",
            Body = "First comment",
            PostId = 1
        });
        Add(new Comment
        {
            Id = 2,
            Name = "Test User 2",
            Email = "user2@test.com",
            Body = "Second comment",
            PostId = 1
        });
    }

    public IEnumerable<Comment> GetAll() => _comments.Values;

    public Comment? GetById(int id) => _comments.TryGetValue(id, out var comment) ? comment : null;

    public Comment Add(Comment comment)
    {
        comment.Id = _nextId++;
        _comments[comment.Id] = comment;
        return comment;
    }

    public Comment? Update(int id, Comment updatedComment)
    {
        if (updatedComment == null)
            throw new ArgumentNullException(nameof(updatedComment));

        if (!_comments.TryGetValue(id, out var existingComment))
            return null;

        var newComment = new Comment
        {
            Id = id,
            Name = updatedComment.Name ?? existingComment.Name,
            Email = updatedComment.Email ?? existingComment.Email,
            Body = updatedComment.Body ?? existingComment.Body,
            PostId = updatedComment.PostId != 0 ? updatedComment.PostId : existingComment.PostId
        };

        _comments[id] = newComment;
        return newComment;
    }

    public Comment? PartialUpdate(int id, Dictionary<string, object> updates)
    {
        if (!_comments.TryGetValue(id, out var comment))
        {
            Console.WriteLine($"Comment with id {id} not found");
            return null;
        }

        Console.WriteLine($"Before update: {JsonSerializer.Serialize(comment)}"); 

        var properties = typeof(Comment).GetProperties(BindingFlags.Public | BindingFlags.Instance);
        bool wasUpdated = false;

        foreach (var update in updates)
        {
            var property = properties.FirstOrDefault(p =>
                p.Name.Equals(update.Key, StringComparison.OrdinalIgnoreCase));

            if (property != null && property.CanWrite)
            {
                try
                {
                    object value;
                    if (property.PropertyType == typeof(int))
                    {
                        value = Convert.ToInt32(update.Value);
                    }
                    else if (property.PropertyType == typeof(string))
                    {
                        value = update.Value.ToString();
                    }
                    else
                    {
                        value = Convert.ChangeType(update.Value, property.PropertyType);
                    }

                    property.SetValue(comment, value);
                    wasUpdated = true;
                    Console.WriteLine($"Updated {property.Name} to {value}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error setting property {update.Key}: {ex.Message}");
                }
            }
        }

        if (wasUpdated)
        {
            _comments[id] = comment;
            Console.WriteLine($"After update: {JsonSerializer.Serialize(_comments[id])}"); 
            return comment;
        }

        Console.WriteLine("No fields were updated");
        return null;
    }

    public Comment? Delete(int id)
    {
        if (!_comments.TryGetValue(id, out var comment))
            return null;

        _comments.Remove(id);
        return comment;
    }
}