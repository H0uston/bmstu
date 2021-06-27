using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLProgressRepository : IProgress
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLProgressRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<Progress> GetAll()
        {
            return _db.Progress;
        }

        public Progress GetElement(int id)
        {
            return _db.Progress.Find(id);
        }

        public void Create(Progress item)
        {
            _db.Progress.Add(item);
        }
        public void Update(Progress item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.Progress.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<Progress> Include(params Expression<Func<Progress, object>>[] includeProperties)
        {
            IQueryable<Progress> query = _db.Progress;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.Progress.Find(id) != null;
        }
    }
}
