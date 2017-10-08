using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Hades.Data.Models.Players.Inventory
{
    public class PlayerBadge
    {
        [Key]
        public int Id { get; set; }

        public int PlayerId { get; set; }

        public string BadgeCode { get; set; }

        public int Slot { get; set; }
    }
}
