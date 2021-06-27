using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IGroupDescription
    {
        public IEnumerable<GroupDescription> GetAll();
        public IQueryable<GroupDescription> Include(params Expression<Func<GroupDescription, object>>[] includeProperties);
        public void Create(GroupDescription entity);
        public GroupDescription GetElement(int id);
        public GroupDescription GetElementByName(string name);
        public void Update(GroupDescription entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);

        public DbSet<Category> GetCategories();
    }
}
