using DistanceLearning.Controllers;
using DistanceLearning.Repositories.interfaces;
using DistanceLearning.ViewModels;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace DistanceLearning.Business_logic
{
    public class HomeLogic
    {
        private readonly IGroupDescription _groupDescription;
        private readonly IParticipation _participation;
        private readonly IUserDescription _userDescription;
        private readonly IRequestList _requestList;


        public HomeLogic(
            IGroupDescription groupDescription,
            IParticipation participation,
            IUserDescription userDescription,
            IRequestList requestList)
        {
            _groupDescription = groupDescription;
            _participation = participation;
            _userDescription = userDescription;
            _requestList = requestList;
        }

        public HomeGroupsViewModel FormHomeModel(string email)
        {
            var part = _participation.GetAll();

            var user = _userDescription.GetElementByEmail(email);
            var groups = _groupDescription.GetAll();

            List<KeyValuePair<bool, bool>> valuePair = new List<KeyValuePair<bool, bool>>();
            bool isUserAlreadyExistInGroup = false;
            bool isUserAwaitsClaim = false;

            if (user is null)
                return new HomeGroupsViewModel(user, groups, valuePair);

            for (int gr = 0; gr < groups.Count(); gr++)
            {
                if (_participation.GetParticipationByUserAndGroup(user.Id, groups.ElementAt(gr).Id) != null)
                {
                    isUserAwaitsClaim = false;
                    isUserAlreadyExistInGroup = true;
                }
                else
                {
                    var rq = _requestList.GetRequestByUserAndGroup(user.Id, groups.ElementAt(gr).Id);
                    if (rq != null)
                    {
                        if (rq.IsAwaiting == true)
                        {
                            isUserAlreadyExistInGroup = false;
                            isUserAwaitsClaim = true;
                        }
                        else
                        {
                            isUserAlreadyExistInGroup = false;
                            isUserAwaitsClaim = false;
                        }
                    }
                    else
                    {
                        isUserAlreadyExistInGroup = false;
                        isUserAwaitsClaim = false;
                    }
                }
                valuePair.Add(new KeyValuePair<bool, bool>(isUserAlreadyExistInGroup, isUserAwaitsClaim));
            }

            return new HomeGroupsViewModel(user, groups, valuePair);
        }
    }
}
