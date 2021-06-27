using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace DistanceLearning.ViewModels
{
    public class AccountDetailsModel
    {
        public string Name { get; set; }

        public string Email { get; set; }

        public string Date { get; set; }

        public int? University { get; set; }
        
        [DataType(DataType.Password)]
        public string Old_password { get; set; }

        [DataType(DataType.Password)]
        public string New_password { get; set; }

        [DataType(DataType.Password)]
        public string Confirm_Password { get; set; }

        public List<GroupDescription> Groups { get; set; }

        public List<University> Universities { get; set; }
    }
}
