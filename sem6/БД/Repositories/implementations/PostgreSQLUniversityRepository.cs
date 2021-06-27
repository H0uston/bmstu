using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLUniversityRepository : IUniversity
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLUniversityRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<University> GetAll()
        {
            return _db.University;
        }

        public University GetElement(int id)
        {
            return _db.University.Find(id);
        }

        public void Create(University item)
        {
            _db.University.Add(item);
        }
        public void Update(University item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.University.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<University> Include(params Expression<Func<University, object>>[] includeProperties)
        {
            IQueryable<University> query = _db.University;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.University.Find(id) != null;
        }
    }
}
