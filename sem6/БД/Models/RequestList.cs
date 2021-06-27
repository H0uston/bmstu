using System;
using System.Collections.Generic;

namespace DistanceLearning
{
    public partial class RequestList
    {
        public int UserId { get; set; }
        public int GroupId { get; set; }
        public bool IsAwaiting { get; set; }
        public bool IsAccepted { get; set; }
        public bool IsDenied { get; set; }

        public virtual GroupDescription Group { get; set; }
        public virtual UserDescription User { get; set; }
    }
}
