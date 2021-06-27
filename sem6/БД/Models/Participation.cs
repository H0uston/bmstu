using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class Participation
    {
        public int UserId { get; set; }
        public int Role { get; set; }
        public int GroupId { get; set; }
        public int? ProgressId { get; set; }

        public virtual GroupDescription Group { get; set; }
        public virtual Progress Progress { get; set; }
        public virtual Role RoleNavigation { get; set; }
        public virtual UserDescription User { get; set; }
    }
}
