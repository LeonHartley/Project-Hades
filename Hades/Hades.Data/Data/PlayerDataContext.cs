using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Hades.Data.Data.Models;

namespace Hades.Data.Models
{
    public class PlayerDataContext : DbContext
    {
        public PlayerDataContext (DbContextOptions<PlayerDataContext> options)
            : base(options)
        {
        }

        public DbSet<PlayerData> PlayerData { get; set; }
    }
}
