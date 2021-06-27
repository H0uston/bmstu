using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using System.Collections;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLUserDescriptionRepository : IUserDescription
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLUserDescriptionRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public DbSet<University> GetUniversities()
        {
            return _db.University;
        }

        public IEnumerable<UserDescription> GetAll()
        {
            return _db.UserDescription;
        }

        public UserDescription GetElement(int id)
        {
            return _db.UserDescription.Find(id);
        }

        public UserDescription GetElementByEmail(string email)
        {
            return _db.UserDescription.FirstOrDefault(u => u.Email == email);
        }

        public void Create(UserDescription item)
        {
            _db.UserDescription.Add(item);
        }
        public void Update(UserDescription item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.UserDescription.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<UserDescription> Include(params Expression<Func<UserDescription, object>>[] includeProperties)
        {
            IQueryable<UserDescription> query = _db.UserDescription;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.UserDescription.Find(id) != null;
        }
    }
}
