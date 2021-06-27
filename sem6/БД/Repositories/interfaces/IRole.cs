using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IRole
    {
        public IEnumerable<Role> GetAll();
        public IQueryable<Role> Include(params Expression<Func<Role, object>>[] includeProperties);
        public void Create(Role entity);
        public Role GetElement(int id);
        public void Update(Role entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);
    }
}
