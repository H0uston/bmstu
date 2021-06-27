using DistanceLearning.ViewModels;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using DistanceLearning.Repositories.interfaces;
using Microsoft.AspNetCore.Razor.TagHelpers;
using Microsoft.VisualStudio.Web.CodeGeneration;
using Microsoft.AspNetCore.Authorization;
using System.Web;
using Microsoft.AspNetCore.WebUtilities;
using Microsoft.AspNetCore.Http;
using System.Text.RegularExpressions;
using System.IO;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Hosting;
using MimeKit;
using DistanceLearning.Business_logic;

namespace DistanceLearning.Controllers
{
    public class GroupController : Controller
    {
        private readonly IGroupDescription _groupRepo;
        private readonly IRequestList _requestListRepo;
        private readonly IUserDescription _userRepo;
        private readonly IParticipation _participationRepo;
        private readonly IFile _filesRepo;
        private readonly IRole _roleRepo;
        private readonly IWebHostEnvironment _appEnviron;
        private readonly GroupLogic _groupLogic;

        public GroupController(IGroupDescription group, IRequestList requestList, IUserDescription users, IParticipation participation,
                               IFile files, IWebHostEnvironment appEnviron, IRole role)
        {
            _groupRepo = group;
            _requestListRepo = requestList;
            _userRepo = users;
            _participationRepo = participation;
            _filesRepo = files;
            _appEnviron = appEnviron;
            _roleRepo = role;
            _groupLogic = new GroupLogic(group, requestList, users, participation, files, appEnviron, role);
        }

        [Authorize]
        [HttpGet]
        public async Task<IActionResult> GroupDetails(int groupId)
        {
            GroupModel group = _groupLogic.FormGroupModel(groupId, User.Identity.Name);
            
            if (group == null)
                return NotFound();

            return View(group);;
        }

        [Authorize]
        public async Task<IActionResult> Edit_info(GroupDescription model)
        {
            bool isGroupEdited = _groupLogic.EditGroupInfo(model);

            if (isGroupEdited)
            {
                GroupModel group = _groupLogic.FormGroupModel(model.Id, User.Identity.Name);

                return View("~/Views/Group/GroupDetails.cshtml", group);
            }
            else
            {
                GroupModel group = _groupLogic.FormGroupModel(model.Id, User.Identity.Name);

                ModelState.AddModelError("error_message", "Имя занято");

                return View("~/Views/Group/GroupDetails.cshtml", group);
            }
        }

        [Authorize]
        [HttpPost]
        public async Task<IActionResult> Load_file(GroupModel model)
        {
            Uri req = new Uri(Request.Headers["Referer"]);
            int groupId = Int32.Parse(HttpUtility.ParseQueryString(req.Query)["groupId"]);
            model.Id = groupId;

            bool isFileLoaded = await _groupLogic.LoadGroupFile(model, User.Identity.Name);

            if (isFileLoaded)
            {
                GroupModel group = _groupLogic.FormGroupModel(model.Id, User.Identity.Name);

                return View("~/Views/Group/GroupDetails.cshtml", group);
            }
            else
            {
                ModelState.AddModelError("error_message", "Ошибка!");
                GroupModel group = _groupLogic.FormGroupModel(model.Id, User.Identity.Name);

                return View("~/Views/Group/GroupDetails.cshtml", group);
            }
        }

        public async Task<IActionResult> AcceptUser(int userId, int groupId)
        {
            _groupLogic.AcceptGroupUser(userId, groupId);

            GroupModel group = _groupLogic.FormGroupModel(groupId, User.Identity.Name);

            return View("~/Views/Group/GroupDetails.cshtml", group);
        }

        public async Task<IActionResult> DenyUser(int userId, int groupId)
        {
            _groupLogic.DenyGroupUser(userId, groupId);

            GroupModel group = _groupLogic.FormGroupModel(groupId, User.Identity.Name);

            return View("~/Views/Group/GroupDetails.cshtml", group);
        }

        public async Task<IActionResult> DeleteFile(int fileId, int groupId)
        {
            _groupLogic.DeleteGroupFile(fileId, groupId);

            GroupModel group = _groupLogic.FormGroupModel(groupId, User.Identity.Name);

            return View("~/Views/Group/GroupDetails.cshtml", group);
        }

        public async Task<IActionResult> DeleteUser(int userId, int groupId)
        {
            _groupLogic.DeleteGroupUser(userId, groupId);

            GroupModel group = _groupLogic.FormGroupModel(groupId, User.Identity.Name);

            return View("~/Views/Group/GroupDetails.cshtml", group);
        }

        public async Task<IActionResult> LeaveGroup(int userId, int groupId)
        {
            _groupLogic.LeaveGroupUser(userId, groupId);

            GroupModel group = _groupLogic.FormGroupModel(groupId, User.Identity.Name);

            return RedirectToRoute(new { controller = "Home", action = "Index" });
        }

        public async Task<IActionResult> DownloadFile(int fileId)
        {
            var file = _filesRepo.GetElement(fileId);
            var path = "C:\\Users\\Houston\\Documents\\GitHub\\DistanceLearning\\wwwroot\\" + file.Path;
            return PhysicalFile(path, MimeTypes.GetMimeType(path), Path.GetFileName(path));
        }

        [Authorize]
        public async Task<IActionResult> CreateGroupIndex()
        {
            return View("~/Views/Group/GroupCreate.cshtml");
        }

        [Authorize]
        [HttpPost]
        public async Task<IActionResult> CreateGroup(GroupModel model)
        {
            bool isGroupCreated = await _groupLogic.CreateGroup(model, User.Identity.Name);
                
            if (isGroupCreated)
            {
                GroupModel group = _groupLogic.FormGroupModel(model.Id, User.Identity.Name);

                return View("~/Views/Group/GroupDetails.cshtml", group);
            }
            else
            {
                ModelState.AddModelError("error_message", "Такая группа уже существует");

                GroupModel group = _groupLogic.FormGroupModel(model.Id, User.Identity.Name);

                return View("~/Views/Group/GroupDetails.cshtml", group);
            }
        }
    }
}
