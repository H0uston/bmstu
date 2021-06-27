using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.implementations
{
    public class PostgreSQLCategoryRepository : ICategory
    {
        private DistanceLearningDBContext _db;

        public PostgreSQLCategoryRepository(DistanceLearningDBContext context)
        {
            this._db = context;
        }

        public IEnumerable<Category> GetAll()
        {
            return _db.Category;
        }

        public Category GetElement(int id)
        {
            return _db.Category.Find(id);
        }

        public void Create(Category item)
        {
            _db.Category.Add(item);
        }
        public void Update(Category item)
        {
            _db.Entry(item).State = EntityState.Modified;
        }
        public void Delete(int id)
        {
            if (this.Exists(id))
            {
                _db.Category.Remove(this.GetElement(id));
                _db.SaveChanges();
            }
        }

        public void Save()
        {
            _db.SaveChanges();
        }

        public IQueryable<Category> Include(params Expression<Func<Category, object>>[] includeProperties)
        {
            IQueryable<Category> query = _db.Category;
            return includeProperties
                .Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }

        public bool Exists(int id)
        {
            return _db.Category.Find(id) != null;
        }
    }
}
