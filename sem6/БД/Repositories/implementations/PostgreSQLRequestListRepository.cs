using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLRequestListRepository : IRequestList
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLRequestListRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<RequestList> GetAll()
        {
            return _db.RequestList;
        }
        public RequestList GetElement(int userId, int groupId)
        {
            return _db.RequestList.Where(u => u.UserId == userId && u.GroupId == groupId).FirstOrDefault();
        }
        public RequestList GetRequestByUserAndGroup(int userId, int groupId)
        {
            return _db.RequestList.Where(rl => rl.UserId == userId && rl.GroupId == groupId).FirstOrDefault();
        }

        public void Create(RequestList item)
        {
            _db.RequestList.Add(item);
        }
        public void Update(RequestList item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int userId, int groupId)
        {
            if (this.Exists(userId, groupId))
            {
                _db.RequestList.Remove(this.GetElement(userId, groupId));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<RequestList> Include(params Expression<Func<RequestList, object>>[] includeProperties)
        {
            IQueryable<RequestList> query = _db.RequestList;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int userId, int groupId)
        {
            return this.GetElement(userId, groupId) != null;
        }

        public DbSet<GroupDescription> GetGroupDescriptions()
        {
            return _db.GroupDescription;
        }

        public DbSet<UserDescription> GetUserDescriptions()
        {
            return _db.UserDescription;
        }

        public List<RequestList> GetElementsForGroup(int id)
        {
            return _db.RequestList.Where(u => u.GroupId == id).ToList();
        }
    }
}
