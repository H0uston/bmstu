﻿using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text.Json;
using System.Text.Json.Serialization;

#nullable disable

namespace Shopich.Models
{
    public partial class Order
    {
        public Order()
        {
            OrderCollection = new HashSet<Orders>();
        }

        public int OrderId { get; set; }
        public int UserId { get; set; }
        public DateTime? OrderDate { get; set; }
        public bool IsApproved { get; set; }
        [IgnoreDataMember]
        [JsonIgnore]
        public virtual User User { get; set; }
        [IgnoreDataMember]
        [JsonIgnore]
        public virtual ICollection<Orders> OrderCollection { get; set; }
    }
}
