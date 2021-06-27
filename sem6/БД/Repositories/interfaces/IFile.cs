using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IFile
    {
        public IEnumerable<Files> GetAll();
        public IQueryable<Files> Include(params Expression<Func<Files, object>>[] includeProperties);
        public void Create(Files entity);
        public Files GetElement(int id);
        public void Update(Files entity);
        public void Delete(int id);
        public void Save();
        public bool Exists(int id);

        public DbSet<GroupDescription> GetGroupDescriptions();
        public DbSet<UserDescription> GetUserDescriptions();

        public List<Files> GetFilesForGroup(int groupId);
    }
}
