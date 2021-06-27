using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class University
    {
        public University()
        {
            UserDescription = new HashSet<UserDescription>();
        }

        public int Id { get; set; }
        public string Name { get; set; }

        public virtual ICollection<UserDescription> UserDescription { get; set; }
    }
}
