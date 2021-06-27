using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using Microsoft.Owin.Security.DataHandler.Encoder;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLGroupDescriptionRepository : IGroupDescription
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLGroupDescriptionRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<GroupDescription> GetAll()
        {
            return _db.GroupDescription;
        }

        public GroupDescription GetElement(int id)
        {
            return _db.GroupDescription.Find(id);
        }

        public GroupDescription GetElementByName(string name)
        {
            return _db.GroupDescription.FirstOrDefault(u => u.Name == name);
        }

        public void Create(GroupDescription item)
        {
            _db.GroupDescription.Add(item);
        }
        public void Update(GroupDescription item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.GroupDescription.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<GroupDescription> Include(params Expression<Func<GroupDescription, object>>[] includeProperties)
        {
            IQueryable<GroupDescription> query = _db.GroupDescription;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.GroupDescription.Find(id) != null;
        }

        public DbSet<Category> GetCategories()
        {
            return _db.Category;
        }
    }
}
