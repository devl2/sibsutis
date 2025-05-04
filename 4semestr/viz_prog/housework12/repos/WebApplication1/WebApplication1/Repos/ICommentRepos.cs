using CommentApi.Models;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CommentApi.Repositories;

public interface ICommentRepository
{
    Task<IEnumerable<Comment>> GetAll();
    Task<Comment?> GetById(int id);
    Task<Comment> Add(Comment comments);
    Task<Comment?> Update(int id, Comment comments);
    Task<Comment?> PartialUpdate(int id, Dictionary<string, object> patch);
    Task<Comment?> Delete(int id);
}