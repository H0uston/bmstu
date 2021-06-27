using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace DistanceLearning.ViewModels
{
    public class RegisterModel
    {
        [Required(ErrorMessage = "Не указаны ФИО")]
        public string name { get; set; }

        [Required(ErrorMessage = "Не указан Email")]
        public string Email { get; set; }

        public int? University { get; set; }

        public string BirthDate { get; set; }

        [Required(ErrorMessage = "Не указан пароль")]
        [DataType(DataType.Password)]
        public string Password { get; set; }

        [DataType(DataType.Password)]
        [Compare("Password", ErrorMessage = "Пароль введён неверно")]
        public string ConfirmPassword { get; set; }

        public List<University> Universities { get; set; }
    }
}
