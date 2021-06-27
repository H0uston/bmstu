using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class Role
    {
        public Role()
        {
            Participation = new HashSet<Participation>();
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public virtual ICollection<Participation> Participation { get; set; }
    }
}
