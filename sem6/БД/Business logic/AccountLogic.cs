using DistanceLearning.Repositories.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Http;
using DistanceLearning.ViewModels;
using System.Reflection.Metadata;


namespace DistanceLearning.Business_logic
{
    public class AccountLogic
    {
        public const int OK = 0;
        public const int WRONG_DATA = 1;
        public const int CONFIRMED_WRONG = 2;

        private readonly IUserDescription _userRepo;
        private readonly IUniversity _universityRepo;
        private readonly IParticipation _participationRepo;
        private readonly IUniversity _universitiesRepo;

        public AccountLogic(IUserDescription users, IUniversity university, IParticipation part)
        {
            _userRepo = users;
            _universityRepo = university;
            _participationRepo = part;
            _universitiesRepo = university;
        }
        
        public bool Login(string email, string password)
        {
            UserDescription user = _userRepo.GetAll().FirstOrDefault(
                    u => email.ToLower() == email.ToLower() && u.Password == password);

            if (user != null)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public ClaimsPrincipal Authenticate(string email)
        {
            UserDescription user = _userRepo.GetElementByEmail(email);
            var claims = new List<Claim>
            {
                new Claim(ClaimsIdentity.DefaultNameClaimType, user.Email),
                new Claim(ClaimsIdentity.DefaultRoleClaimType, user.Role)
            };

            ClaimsIdentity id = new ClaimsIdentity(claims, "ApplicationCookie", ClaimsIdentity.DefaultNameClaimType, ClaimsIdentity.DefaultRoleClaimType);

            return new ClaimsPrincipal(id);
        }

        public RegisterModel FormRegisterModel()
        {
            RegisterModel model = new RegisterModel();
            model.Universities = _universityRepo.GetAll().ToList();

            return model;
        }

        public bool Register(RegisterModel model)
        {
            UserDescription user = _userRepo.GetAll().FirstOrDefault(
                    u => u.Email.ToLower() == model.Email.ToLower());
            if (user == null)
            {
                if (model.University != 0) // Означает, что университет выбран
                {
                    if (model.BirthDate == null)
                    {
                        user = new UserDescription
                        {
                            Name = model.name,
                            Email = model.Email,
                            Password = model.Password,
                            University = model.University,
                            Role = "User"
                        };
                    }
                    else
                    {
                        user = new UserDescription
                        {
                            Name = model.name,
                            Email = model.Email,
                            Password = model.Password,
                            Birthday = DateTime.Parse(model.BirthDate),
                            University = model.University,
                            Role = "User"
                        };
                    }
                }
                else
                {
                    if (model.BirthDate == null)
                        user = new UserDescription
                        {
                            Name = model.name,
                            Email = model.Email,
                            Password = model.Password,
                            Role = "User"
                        };
                    else
                        user = new UserDescription
                        {
                            Name = model.name,
                            Email = model.Email,
                            Password = model.Password,
                            Birthday = DateTime.Parse(model.BirthDate),
                            Role = "User"
                        };
                }
                _userRepo.Create(user);
                _userRepo.Save();

                ClaimsPrincipal id = Authenticate(model.Email);

                return true;
            }
            else
            {
                return false;
            }
        }

        public AccountDetailsModel FormAccountDetailsModel(string email)
        {
            AccountDetailsModel account = new AccountDetailsModel();
            account.Universities = _universityRepo.GetAll().ToList();

            var user = _userRepo.GetElementByEmail(email);

            account.Name = user.Name;
            account.Email = user.Email;
            account.University = user.University;
            account.Groups = _participationRepo.GetGroupsForUser(user.Id);

            if (user.Birthday.ToString() == "01.01.0001 0:00:00")
            {
                account.Date = "";
            }
            else
            {
                account.Date = user.Birthday.ToString();
            }

            return account; 
        }

        public int EditAccountDetailsModel(AccountDetailsModel changes, string email)
        {
            UserDescription old_user = _userRepo.GetElementByEmail(email);

            if (changes.Email.ToLower() != old_user.Email.ToLower())
            {
                var some_user = _userRepo.GetElementByEmail(changes.Email);
                if (some_user == null)
                {
                    old_user.Email = changes.Email;
                }
                else
                    return WRONG_DATA; // Почта занята
            }

            if (changes.Name != old_user.Name)
            {
                old_user.Name = changes.Name;
            }

            if (changes.Date != old_user.Birthday.ToString() && !(changes.Date is null))
            {
                old_user.Birthday = DateTime.Parse(changes.Date);
            }

            if (changes.University != old_user.University)
            {
                old_user.University = changes.University;
            }

            _userRepo.Update(old_user);
            _userRepo.Save();

            return OK;  // Изменения сохранены
        }

        public int ChangePassword(AccountDetailsModel changes, string email)
        {
            var user = _userRepo.GetElementByEmail(email);

            if (user.Password == changes.Old_password)
            {
                if (changes.New_password == changes.Confirm_Password)
                {
                    user.Password = changes.New_password;
                    _userRepo.Update(user);
                    _userRepo.Save();
                    return 0;
                }
                else
                    return CONFIRMED_WRONG; // Пароль повторён неверно
            }
            else
                return WRONG_DATA;  // Старый пароль не совпадает
        }
    }
}
