using CommentApi.Models;
using CommentApi.Services;
using Microsoft.AspNetCore.Mvc;

namespace CommentApi.Controllers;

public static class CommentsController
{
    public static void MapCommentsRoutes(this WebApplication app)
    {
        app.MapGet("/comments", async (CommentService service, ILogger<Program> logger) =>
        {
            logger.LogInformation("Getting all comments");
            try
            {
                var comments = await service.GetAll();
                logger.LogInformation("Retrieved {Count} comments", comments.Count());
                return Results.Ok(comments);
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error retrieving comments");
                return Results.Problem("Error retrieving comments");
            }
        });

        app.MapGet("/comments/{id}", async (int id, CommentService service, ILogger<Program> logger) =>
        {
            logger.LogInformation("Getting comment with ID: {Id}", id);
            try
            {
                var comment = await service.GetById(id);
                if (comment is not null)
                {
                    logger.LogInformation("Found comment with ID: {Id}", id);
                    return Results.Ok(comment);
                }
                logger.LogWarning("Comment with ID: {Id} not found", id);
                return Results.NotFound();
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error retrieving comment with ID: {Id}", id);
                return Results.Problem("Error retrieving comment");
            }
        });

        app.MapPost("/comments", async (Comment comment, CommentService service, ILogger<Program> logger) =>
        {
            logger.LogInformation("Creating new comment: {@Comment}", comment);
            try
            {
                var createdComment = await service.Add(comment);
                logger.LogInformation("Created comment with ID: {Id}", createdComment.Id);
                return Results.Created($"/comments/{createdComment.Id}", createdComment);
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error creating comment");
                return Results.Problem("Error creating comment");
            }
        });

        app.MapPut("/comments/{id}", async (int id, Comment updatedComment, CommentService service, ILogger<Program> logger) =>
        {
            logger.LogInformation("Updating comment with ID: {Id}, data: {@Comment}", id, updatedComment);
            try
            {
                var result = await service.Update(id, updatedComment);
                if (result is not null)
                {
                    logger.LogInformation("Updated comment with ID: {Id}", id);
                    return Results.Ok(result);
                }
                logger.LogWarning("Comment with ID: {Id} not found for update", id);
                return Results.NotFound();
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error updating comment with ID: {Id}", id);
                return Results.Problem("Error updating comment");
            }
        });

        app.MapPatch("/comments/{id}", async (int id, Dictionary<string, object> updates, CommentService service, ILogger<Program> logger) =>
        {
            logger.LogInformation("Partially updating comment with ID: {Id}, updates: {@Updates}", id, updates);
            try
            {
                var result = await service.PartialUpdate(id, updates);
                if (result is not null)
                {
                    logger.LogInformation("Partially updated comment with ID: {Id}", id);
                    return Results.Ok(result);
                }
                logger.LogWarning("Comment with ID: {Id} not found for partial update", id);
                return Results.NotFound();
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error partially updating comment with ID: {Id}", id);
                return Results.Problem("Error partially updating comment");
            }
        });

        app.MapDelete("/comments/{id}", async (int id, CommentService service, ILogger<Program> logger) =>
        {
            logger.LogInformation("Deleting comment with ID: {Id}", id);
            try
            {
                var deletedComment = await service.Delete(id);
                if (deletedComment is not null)
                {
                    logger.LogInformation("Deleted comment with ID: {Id}", id);
                    return Results.Ok(deletedComment);
                }
                logger.LogWarning("Comment with ID: {Id} not found for deletion", id);
                return Results.NotFound();
            }
            catch (Exception ex)
            {
                logger.LogError(ex, "Error deleting comment with ID: {Id}", id);
                return Results.Problem("Error deleting comment");
            }
        });
    }
}