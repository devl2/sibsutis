using System.Xml.Linq;
using CommentApi.Models;
using CommentApi.Services;
using Microsoft.AspNetCore.Mvc;

namespace CommentApi.Controllers;

public static class CommentsController
{
    public static void MapCommentsRoutes(this WebApplication app)
    {
        app.MapGet("/comments", (CommentService service) =>
        {
            var comments = service.GetAll();
            return Results.Ok(comments);
        });

        app.MapGet("/comments/{id}", (int id, CommentService service) =>
        {
            var comment = service.GetById(id);
            return comment is not null ? Results.Ok(comment) : Results.NotFound();
        });

        app.MapPost("/comments", (Comment comment, CommentService service) =>
        {
            var createdComment = service.Add(comment);
            return Results.Created($"/comments/{createdComment.Id}", createdComment);
        });

        app.MapPut("/comments/{id}", (int id, Comment updatedComment, CommentService service) =>
        {
            var result = service.Update(id, updatedComment);
            return result is not null ? Results.Ok(result) : Results.NotFound();
        });

        app.MapPatch("/comments/{id}", (int id, Dictionary<string, object> updates, CommentService service) =>
        {
            var result = service.PartialUpdate(id, updates);
            return result is not null ? Results.Ok(result) : Results.NotFound();
        });

        app.MapDelete("/comments/{id}", (int id, CommentService service) =>
        {
            var deletedComment = service.Delete(id);
            return deletedComment is not null ? Results.Ok(deletedComment) : Results.NotFound();
        });
    }
}