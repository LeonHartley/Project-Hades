using Hades.Data.Models.Players;
using Hades.Data.Models.Players.Inventory;
using Hades.Data.Models.Players.Messenger;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;

namespace Hades.Data.Context
{
    public class PlayerContext : DbContext
    {
        public PlayerContext (DbContextOptions<PlayerContext> options)
            : base(options)
        {
        }

        public DbSet<Player> PlayerData { get; set; }

        public DbSet<PlayerFriendship> PlayerFriendships { get; set; }

        public DbSet<PlayerBadge> PlayerBadges { get; set; }
        
        public DbSet<InventoryItem> InventoryItems { get; set; }
    }
}
