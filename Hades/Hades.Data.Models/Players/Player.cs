using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using Hades.API.Players;
using Hades.API.Players.Data;
using Hades.Data.Models.Players.Inventory;
using Hades.Data.Models.Players.Messenger;

namespace Hades.Data.Models.Players
{
    public class Player : IPlayerData
    {
        [Key]
        public int Id { get; set; }
        
        public string Username { get; set; }
        
        public string Figure { get; set; }
        
        public string Motto { get; set; }
        
        public string AuthenticationToken { get; set; }
        
        public int Coins { get; set; }

        public int VipPoints { get; set; }

        public int ActivityPoints { get; set; }

        public PlayerGender Gender { get; set; }
        
        public virtual List<PlayerFriendship> Friendships { get; set; }

        public virtual List<InventoryItem> Inventory { get; set; }

        public virtual List<PlayerBadge> Badges { get; set; }
    }
}