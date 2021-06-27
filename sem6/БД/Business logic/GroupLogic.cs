using DistanceLearning.Repositories.interfaces;
using DistanceLearning.ViewModels;
using Microsoft.AspNetCore.Hosting;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Web;

namespace DistanceLearning.Business_logic
{
    public class GroupLogic
    {
        private readonly IGroupDescription _groupRepo;
        private readonly IRequestList _requestListRepo;
        private readonly IUserDescription _userRepo;
        private readonly IParticipation _participationRepo;
        private readonly IFile _filesRepo;
        private readonly IRole _roleRepo;
        private readonly IWebHostEnvironment _appEnviron;

        public GroupLogic(IGroupDescription group, IRequestList requestList, IUserDescription users, IParticipation participation,
                               IFile files, IWebHostEnvironment appEnviron, IRole role)
        {
            _groupRepo = group;
            _requestListRepo = requestList;
            _userRepo = users;
            _participationRepo = participation;
            _filesRepo = files;
            _appEnviron = appEnviron;
            _roleRepo = role;
        }

        public GroupModel FormGroupModel(int groupId, string email)
        {
            GroupDescription group = _groupRepo.GetElement(groupId); // Информация о текущей группе

            if (group == null)
            {
                return null;
            }

            UserDescription user = _userRepo.GetElementByEmail(email);
            var part = _participationRepo.GetElement(user.Id, groupId);
            string role = null;
            if (part == null && !group.Private)
            {
                _participationRepo.Create(new Participation { UserId = user.Id, GroupId = groupId, Role = 0 });
                _participationRepo.Save();
                role = _roleRepo.GetElement(0).Name;
            }
            else
            {
                role = _roleRepo.GetElement(part.Role).Name;
            }

            List<RequestList> requests = _requestListRepo.GetElementsForGroup(groupId); // Список заявок в текущую группу
            List<UserDescription> requested_users = new List<UserDescription>(); // Пользователи подавшие заявку
            for (int i = 0; i < requests.Count(); i++)
            {
                requested_users.Add(_userRepo.GetElement(requests[i].UserId));
            }

            List<Participation> users_ids = _participationRepo.GetUsersForGroup(groupId); // список id участников текущей группы
            List<UserDescription> users = new List<UserDescription>();  // участники текущей группы
            for (int i = 0; i < users_ids.Count(); i++)
            {
                users.Add(_userRepo.GetElement(users_ids[i].UserId));
                users[i].Role = _roleRepo.GetElement(_participationRepo.GetElement(users[i].Id, groupId).Role).Name;
            }
            List<Files> files = _filesRepo.GetFilesForGroup(groupId);  // загруженные материалы текущей группы

            return new GroupModel
            {
                Id = group.Id,
                Name = group.Name,
                requests = requested_users,
                members = users,
                files = files,
                Private = group.Private,
                Role = role
            };
        }

        public bool EditGroupInfo(GroupDescription model)
        {
            GroupDescription group = _groupRepo.GetElement(model.Id);
            var elem = _groupRepo.GetElementByName(model.Name);

            if (elem == null)
            {
                group.Name = model.Name;
            }
            else if (model.Name != group.Name)
            {
                return false;
            }

            group.Private = model.Private;
            _groupRepo.Update(group);
            _groupRepo.Save();
            return true;
        }

        public async Task<bool> LoadGroupFile(GroupModel model, string email)
        {
            int userId = _userRepo.GetElementByEmail(email).Id;
            string path = null;
            string error_message = null;

            if (model.File != null)
            {
                string expansion = model.File.FileName.Substring(model.File.FileName.LastIndexOf("."));
                path = "/files/" + Guid.NewGuid() + expansion;
                using (var fileStream = new FileStream(_appEnviron.WebRootPath + path, FileMode.Create))
                {
                    await model.File.CopyToAsync(fileStream);
                }

                DateTime thisDay = DateTime.Today;

                _filesRepo.Create(new Files
                {
                    Name = model.File.FileName,
                    Path = path,
                    DateOfLoad = thisDay,
                    Owner = userId,
                    GroupId = model.Id
                });
                _filesRepo.Save();
                return true;
            }
            else
            {
                return false;
            }
        }

        public void AcceptGroupUser(int userId, int groupId)
        {
            _participationRepo.Create(new Participation { UserId = userId, GroupId = groupId, Role = 0 });
            _participationRepo.Save();
            _requestListRepo.Delete(userId, groupId);
            _participationRepo.Save();
        }

        public void DenyGroupUser(int userId, int groupId)
        {
            _requestListRepo.Delete(userId, groupId);
            _participationRepo.Save();
        }

        public void DeleteGroupFile(int fileId, int groupId)
        {
            _filesRepo.Delete(fileId);
            _filesRepo.Save();
        }

        public void DeleteGroupUser(int userId, int groupId)
        {
            _participationRepo.Delete(userId, groupId);
            _participationRepo.Save();
        }

        public void LeaveGroupUser(int userId, int groupId)
        {
            _participationRepo.Delete(userId, groupId);
            _filesRepo.Save();
        }

        public async Task<bool> CreateGroup(GroupModel group, string email)
        {
            var some_group = _groupRepo.GetElementByName(group.Name);
            if (some_group == null)
            {
                string path;
                if (group.Image != null) // Файл загружен
                {
                    string expansion = group.Image.FileName.Substring(group.Image.FileName.LastIndexOf("."));
                    path = "/img/group_icons/" + Guid.NewGuid() + expansion;
                    using (var fileStream = new FileStream(_appEnviron.WebRootPath + path, FileMode.Create))
                    {
                        await group.Image.CopyToAsync(fileStream);
                    }
                }
                else
                {
                    path = "/img/group_icons/default_image.png"; // Ставится стоковое изображение
                }
                // Создаётся группа
                _groupRepo.Create(new GroupDescription { Name = group.Name, Private = group.Private, IconPath = path });
                _groupRepo.Save();

                // Создание связи
                _participationRepo.Create(new Participation
                {
                    GroupId = _groupRepo.GetElementByName(group.Name).Id,
                    UserId = _userRepo.GetElementByEmail(email).Id,
                    Role = 2
                });;
                _participationRepo.Save();

                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
