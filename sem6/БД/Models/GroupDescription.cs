using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class GroupDescription
    {
        public GroupDescription()
        {
            Files = new HashSet<Files>();
            Participation = new HashSet<Participation>();
            RequestList = new HashSet<RequestList>();
        }

        public int Id { get; set; }
        public string Name { get; set; }
        public bool Private { get; set; }
        public int? GroupCategory { get; set; }
        public string IconPath { get; set; }

        public virtual Category GroupCategoryNavigation { get; set; }
        public virtual ICollection<Files> Files { get; set; }
        public virtual ICollection<Participation> Participation { get; set; }
        public virtual ICollection<RequestList> RequestList { get; set; }
    }
}
