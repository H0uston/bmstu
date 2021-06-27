using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLRoleRepository : IRole
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLRoleRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<Role> GetAll()
        {
            return _db.Role;
        }

        public Role GetElement(int id)
        {
            return _db.Role.Find(id);
        }

        public void Create(Role item)
        {
            _db.Role.Add(item);
        }
        public void Update(Role item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.Role.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<Role> Include(params Expression<Func<Role, object>>[] includeProperties)
        {
            IQueryable<Role> query = _db.Role;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.Role.Find(id) != null;
        }
    }
}
