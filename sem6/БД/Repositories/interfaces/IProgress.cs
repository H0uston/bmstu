using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IProgress
    {
        public IEnumerable<Progress> GetAll();
        public IQueryable<Progress> Include(params Expression<Func<Progress, object>>[] includeProperties);
        public void Create(Progress entity);
        public Progress GetElement(int id);
        public void Update(Progress entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);
    }
}
