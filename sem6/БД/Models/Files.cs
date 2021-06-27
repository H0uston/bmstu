using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class Files
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Path { get; set; }
        public DateTime DateOfLoad { get; set; }
        public int Owner { get; set; }
        public int GroupId { get; set; }

        public virtual GroupDescription Group { get; set; }
        public virtual UserDescription OwnerNavigation { get; set; }
    }
}
