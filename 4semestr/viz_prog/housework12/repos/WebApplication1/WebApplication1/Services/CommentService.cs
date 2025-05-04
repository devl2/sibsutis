using CommentApi.Models;
using CommentApi.Repositories;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CommentApi.Services;

public class CommentService
{
    private readonly ICommentRepository _repository;

    public CommentService(ICommentRepository repository) 
    {
        _repository = repository;
    }

    public async Task<IEnumerable<Comment>> GetAll() => await _repository.GetAll(); 

    public async Task<Comment?> GetById(int id) => await _repository.GetById(id);

    public async Task<Comment> Add(Comment comment) => await _repository.Add(comment);

    public async Task<Comment?> Update(int id, Comment comment) => await _repository.Update(id, comment);

    public async Task<Comment?> PartialUpdate(int id, Dictionary<string, object> patch) =>
        await _repository.PartialUpdate(id, patch);

    public async Task<Comment?> Delete(int id) => await _repository.Delete(id);
}