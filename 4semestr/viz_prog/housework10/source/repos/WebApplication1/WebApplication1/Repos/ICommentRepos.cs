using CommentApi.Models;

namespace CommentApi.Repositories;

public interface ICommentRepository
{
    IEnumerable<Comment> GetAll();
    Comment? GetById(int id);
    Comment Add(Comment comment);
    Comment? Update(int id, Comment comment);
    Comment? PartialUpdate(int id, Dictionary<string, object> patch);
    Comment? Delete(int id);
}