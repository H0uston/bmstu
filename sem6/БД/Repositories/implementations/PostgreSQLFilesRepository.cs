using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLFilesRepository : IFile
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLFilesRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<Files> GetAll()
        {
            return _db.Files;
        }

        public Files GetElement(int id)
        {
            return _db.Files.Find(id);
        }

        public void Create(Files item)
        {
            _db.Files.Add(item);
        }
        public void Update(Files item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.Files.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<Files> Include(params Expression<Func<Files, object>>[] includeProperties)
        {
            IQueryable<Files> query = _db.Files;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.Files.Find(id) != null;
        }

        public DbSet<GroupDescription> GetGroupDescriptions()
        {
            return _db.GroupDescription;
        }

        public DbSet<UserDescription> GetUserDescriptions()
        {
            return _db.UserDescription;
        }

        public List<Files> GetFilesForGroup(int groupId)
        {
            return _db.Files.Where(u => u.GroupId == groupId).ToList();
        }
    }
}
