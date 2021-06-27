using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class Category
    {
        public Category()
        {
            GroupDescription = new HashSet<GroupDescription>();
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }

        public virtual ICollection<GroupDescription> GroupDescription { get; set; }
    }
}
