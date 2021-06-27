using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IUniversity
    {
        public IEnumerable<University> GetAll();
        public IQueryable<University> Include(params Expression<Func<University, object>>[] includeProperties);
        public void Create(University entity);
        public University GetElement(int id);
        public void Update(University entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);
    }
}
