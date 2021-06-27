using System;
using System.Collections.Generic;
using System.Diagnostics.Eventing.Reader;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IUserDescription
    {
        public IEnumerable<UserDescription> GetAll();
        public IQueryable<UserDescription> Include(params Expression<Func<UserDescription, object>>[] includeProperties);
        public void Create(UserDescription entity);
        public UserDescription GetElement(int id);
        public UserDescription GetElementByEmail(string email);
        public void Update(UserDescription entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);

        public DbSet<University> GetUniversities();

    }
}
