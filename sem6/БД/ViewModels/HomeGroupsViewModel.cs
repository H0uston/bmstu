using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using DistanceLearning.Models;

namespace DistanceLearning.ViewModels
{
    public class HomeGroupsViewModel
    {
        public HomeGroupsViewModel(UserDescription _user, IEnumerable<GroupDescription> _groups, 
            List<KeyValuePair<bool, bool>> _valuePair)
        {
            user = _user;
            groups = _groups;
            valuePair = _valuePair;
        }
        public UserDescription user;
        public IEnumerable<GroupDescription> groups;
        public IEnumerable<Participation> participation;
        public List<KeyValuePair<bool, bool>> valuePair;
    }
}