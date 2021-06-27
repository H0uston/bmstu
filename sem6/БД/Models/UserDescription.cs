using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace DistanceLearning
{
    public partial class UserDescription
    {
        public UserDescription()
        {
            Files = new HashSet<Files>();
            Participation = new HashSet<Participation>();
            RequestList = new HashSet<RequestList>();
        }

        [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
        public int Id { get; set; }
        public string Name { get; set; }
        public string Email { get; set; }
        public string Password { get; set; }
        public DateTime Birthday { get; set; }
        public int? University { get; set; }
        public string Role { get; set; }

        public virtual University UniversityNavigation { get; set; }
        public virtual ICollection<Files> Files { get; set; }
        public virtual ICollection<Participation> Participation { get; set; }
        public virtual ICollection<RequestList> RequestList { get; set; }
    }
}
