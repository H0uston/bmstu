using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class Progress
    {
        public Progress()
        {
            Participation = new HashSet<Participation>();
        }

        public int Id { get; set; }
        public int TotalCountTasks { get; set; }
        public int CompletedTasks { get; set; }

        public virtual ICollection<Participation> Participation { get; set; }
    }
}
