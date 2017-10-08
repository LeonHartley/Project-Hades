using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace Hades.Data.Models.Players.Inventory
{
    public class InventoryItem
    {
        [Key]
        public long Id { get; set; }

        public int PlayerId { get; set; }

        public int ItemId { get; set; }

        public string Data { get; set; }
    }
}
