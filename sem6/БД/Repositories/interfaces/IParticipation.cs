using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace DistanceLearning.Repositories.interfaces
{
    public interface IParticipation
    {
        public IEnumerable<Participation> GetAll();
        public IQueryable<Participation> Include(params Expression<Func<Participation, object>>[] includeProperties);
        public void Create(Participation entity);
        public Participation GetElement(int userId, int groupId);
        public Participation GetParticipationByUserAndGroup(int userId, int groupId);
        public void Update(Participation entity);
        public void Delete(int userId, int groupId);
        public void Save();
        public bool Exists(int userId, int groupId);

        public DbSet<GroupDescription> GetGroupDescriptions();
        public DbSet<UserDescription> GetUserDescriptions();
        public DbSet<Role> GetRoles();
        public DbSet<Progress> GetProgresses();

        public List<Participation> GetUsersForGroup(int groupId);

        public List<GroupDescription> GetGroupsForUser(int userId);
    }
}
