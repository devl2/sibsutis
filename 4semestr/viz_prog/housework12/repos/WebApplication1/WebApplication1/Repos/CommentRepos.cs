using Microsoft.EntityFrameworkCore;
using CommentApi.Models;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Reflection;
using System;

namespace CommentApi.Repositories;

public class CommentRepository : ICommentRepository
{
    private readonly AppDbContext _context;

    public CommentRepository(AppDbContext context)
    {
        _context = context;
    }

    public async Task<IEnumerable<Comment>> GetAll()
    {
        return await _context.Comment.ToListAsync();
    }

    public async Task<Comment?> GetById(int id)
    {
        return await _context.Comment.FindAsync(id);
    }

    public async Task<Comment> Add(Comment comment)
    {
        await _context.Comment.AddAsync(comment);
        await _context.SaveChangesAsync();
        return comment;
    }

    public async Task<Comment?> Update(int id, Comment updatedComment)
    {
        if (updatedComment == null)
            throw new ArgumentNullException(nameof(updatedComment));

        var existingComment = await _context.Comment.FindAsync(id);
        if (existingComment == null)
            return null;

        existingComment.Name = updatedComment.Name ?? existingComment.Name;
        existingComment.Email = updatedComment.Email ?? existingComment.Email;
        existingComment.Body = updatedComment.Body ?? existingComment.Body;
        existingComment.PostId = updatedComment.PostId != 0 ? updatedComment.PostId : existingComment.PostId;

        await _context.SaveChangesAsync();
        return existingComment;
    }

    public async Task<Comment?> PartialUpdate(int id, Dictionary<string, object> updates)
    {
        var comment = await _context.Comment.FindAsync(id);
        if (comment == null)
            return null;

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
                }
                catch (Exception ex)
                {
                    continue;
                }
            }
        }

        if (wasUpdated)
        {
            await _context.SaveChangesAsync();
            return comment;
        }

        return null;
    }

    public async Task<Comment?> Delete(int id)
    {
        var comment = await _context.Comment.FindAsync(id);
        if (comment == null)
            return null;

        _context.Comment.Remove(comment);
        await _context.SaveChangesAsync();
        return comment;
    }
}