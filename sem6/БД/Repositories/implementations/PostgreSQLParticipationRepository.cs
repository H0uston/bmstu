using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLParticipationRepository : IParticipation
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLParticipationRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<Participation> GetAll()
        {
            return _db.Participation;
        }

        public Participation GetElement(int userId, int groupId)
        {
            return _db.Participation.Where(u => u.UserId == userId && u.GroupId == groupId).FirstOrDefault();
        }
        public Participation GetParticipationByUserAndGroup(int userId, int groupId)
        {
            return _db.Participation.Where(p => p.UserId == userId && p.GroupId == groupId).ToList().FirstOrDefault();
        }
        public void Create(Participation item)
        {
            _db.Participation.Add(item);
        }
        public void Update(Participation item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int userId, int groupId)
        {
            if (this.Exists(userId, groupId))
            {
                _db.Participation.Remove(this.GetElement(userId, groupId));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<Participation> Include(params Expression<Func<Participation, object>>[] includeProperties)
        {
            IQueryable<Participation> query = _db.Participation;
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
        public DbSet<Role> GetRoles()
        {
            return _db.Role;
        }
        public DbSet<Progress> GetProgresses()
        {
            return _db.Progress;
        }

        public List<Participation> GetUsersForGroup(int groupId)
        {
            return _db.Participation.Where(u => u.GroupId == groupId).ToList();
        }

        public List<GroupDescription> GetGroupsForUser(int userId)
        {
            var groupIds = _db.Participation.Where(u => u.UserId == userId).ToList();
            
            if (groupIds == null)
            {
                return null;
            }

            List<GroupDescription> groups = new List<GroupDescription>();
            for (int i = 0; i < groupIds.Count(); i++)
            {
                groups.Add(_db.GroupDescription.Find(groupIds[i].GroupId));
            }

            return groups;
        }
    }
}
