using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using DistanceLearning.ViewModels;
using DistanceLearning.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.DataProtection.AuthenticatedEncryption.ConfigurationModel;
using System.Security.Claims;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using DistanceLearning.Repositories.implementations;
using DistanceLearning.Repositories.interfaces;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Authorization;
using System.Globalization;
using Microsoft.AspNetCore.Mvc.Rendering;
using DistanceLearning.Business_logic;

namespace DistanceLearning.Controllers
{
    public class AccountController : Controller
    {
        private readonly IUserDescription _userRepo;
        private readonly IParticipation _participationRepo;
        private readonly IUniversity _universitiesRepo;
        private readonly AccountLogic _accountLogic;

        public AccountController(IUserDescription userInterface, IUniversity university, IParticipation part)
        {
            _userRepo = userInterface;
            _participationRepo = part;
            _universitiesRepo = university;
            _accountLogic = new AccountLogic(userInterface, university, part);
        }

        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Login(LoginModel model)
        {
            if (ModelState.IsValid)
            {
                bool isDataRight = _accountLogic.Login(model.Email, model.Password);
                
                if (isDataRight)
                {
                    ClaimsPrincipal id = _accountLogic.Authenticate(model.Email); // аутентификация
                    await HttpContext.SignInAsync(CookieAuthenticationDefaults.AuthenticationScheme, new ClaimsPrincipal(id));

                    return RedirectToAction("Index", "Home");
                }
                ModelState.AddModelError("Incorrect password", "Некорректные данные");
            }

            return View(model);
        }

        [HttpGet]
        public IActionResult Register()
        {
            RegisterModel model = _accountLogic.FormRegisterModel();

            return View(model);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Register(RegisterModel model)
        {
            if (ModelState.IsValid)
            {
                bool isRegistered = _accountLogic.Register(model);

                if (isRegistered)
                {
                    ClaimsPrincipal id = _accountLogic.Authenticate(model.Email); // аутентификация
                    await HttpContext.SignInAsync(CookieAuthenticationDefaults.AuthenticationScheme, new ClaimsPrincipal(id));

                    return RedirectToAction("Index", "Home");
                }
                else
                {
                    ModelState.AddModelError("error_message", "Почта уже зарегистрирована");
                }

                return RedirectToAction("Index", "Home");
                
            }
            model.Universities = _accountLogic.FormRegisterModel().Universities;

            return View(model);
        }

        

        public async Task<IActionResult> Logout()
        {
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);

            return RedirectToAction("Login", "Account");
        }

        [Authorize]
        [HttpGet]
        public async Task<IActionResult> AccountDetails()
        {
            AccountDetailsModel model = _accountLogic.FormAccountDetailsModel(User.Identity.Name);

            return View(model);
        }

        [HttpPost]
        public async Task<IActionResult> AccountDetails(AccountDetailsModel model)
        {
            return View(model);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(AccountDetailsModel changes)
        {
            int rc = _accountLogic.EditAccountDetailsModel(changes, User.Identity.Name);

            if (rc == AccountLogic.WRONG_DATA)
            {
                ModelState.AddModelError("error_message", "Почта занята!");
            }

            changes = _accountLogic.FormAccountDetailsModel(User.Identity.Name);

            return View("~/Views/Account/AccountDetails.cshtml", changes);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Change_password(AccountDetailsModel changes)
        {
            int rc = _accountLogic.ChangePassword(changes, User.Identity.Name);

            if (rc == AccountLogic.WRONG_DATA)
            {
                ModelState.AddModelError("error_message", "Старый пароль не совпадает");
            }
            else if (rc == AccountLogic.CONFIRMED_WRONG)
            {
                ModelState.AddModelError("error_message", "Пароль повторён неверно");
            }

            changes = _accountLogic.FormAccountDetailsModel(User.Identity.Name);

            return View("~/Views/Account/AccountDetails.cshtml", changes);
        }
    }
}
