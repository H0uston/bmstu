using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IRequestList
    {
        public IEnumerable<RequestList> GetAll();
        public IQueryable<RequestList> Include(params Expression<Func<RequestList, object>>[] includeProperties);
        public void Create(RequestList entity);
        public RequestList GetElement(int userId, int groupId);
        public RequestList GetRequestByUserAndGroup(int userId, int groupId);
        public void Update(RequestList entity);
        public void Delete(int userId, int groupId);
        public void Save();
        public bool Exists(int userId, int groupId);
        public DbSet<GroupDescription> GetGroupDescriptions();
        public DbSet<UserDescription> GetUserDescriptions();

        public List<RequestList> GetElementsForGroup(int id);
    }
}
