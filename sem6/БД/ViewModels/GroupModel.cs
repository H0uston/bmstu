using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace DistanceLearning.ViewModels
{
    public class GroupModel
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public bool Private { get; set; }

        public string Role { get; set; }
        public IFormFile File { get; set; }

        public List<UserDescription> requests { get; set; }
        public List<Files> files { get; set; }
        public List<UserDescription> members { get; set; }
        public IFormFile Image { get; set; }
    }
}
