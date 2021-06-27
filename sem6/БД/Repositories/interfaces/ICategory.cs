using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace DistanceLearning.Repositories.interfaces
{
    public interface ICategory
    {
        public IEnumerable<Category> GetAll();
        public IQueryable<Category> Include(params Expression<Func<Category, object>>[] includeProperties);
        public void Create(Category entity);
        public Category GetElement(int id);
        public void Update(Category entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);
    }
}
