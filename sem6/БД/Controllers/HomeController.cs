using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using DistanceLearning.Models;
using DistanceLearning.ViewModels;
using Microsoft.AspNetCore.Authorization;
using DistanceLearning.Repositories.interfaces;
using DistanceLearning.Business_logic;

namespace DistanceLearning.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly IGroupDescription _groupDescription;
        private readonly IParticipation _participation;
        private readonly IUserDescription _userDescription;
        private readonly IRequestList _requestList;
        private readonly HomeLogic _homeLogic;


        public HomeController(
            ILogger<HomeController> logger, 
            IGroupDescription groupDescription, 
            IParticipation participation,
            IUserDescription userDescription,
            IRequestList requestList)
        {
            _logger = logger;
            _groupDescription = groupDescription;
            _participation = participation;
            _userDescription = userDescription;
            _requestList = requestList;
            _homeLogic = new HomeLogic(_groupDescription, _participation, _userDescription, _requestList);
        }

        public IActionResult Index()
        {
            HomeGroupsViewModel model = _homeLogic.FormHomeModel(User.Identity.Name);

            return View(model);
        }


        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }

    }
}
