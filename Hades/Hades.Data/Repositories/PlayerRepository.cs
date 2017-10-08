using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using Hades.Data.Context;
using Hades.Data.Models.Players;
using Microsoft.EntityFrameworkCore;

namespace Hades.Data.Repositories
{
    public interface IPlayerRepository
    {
        Task<Player> Get(int id);

        Task<Player> GetByAuthenticationToken(string token);

        Task<Player> Create(Player player);

        Task<Player> Update(Player player);
    }

    public class PlayerRepository : IPlayerRepository
    {
        private readonly PlayerContext _playerContext;

        public PlayerRepository(PlayerContext playerContext)
        {
            _playerContext = playerContext;
        }

        public async Task<Player> Get(int id)
        {
            var player = _playerContext.PlayerData.Where(p => p.Id == id);

            return await Load(player);
        }

        public async Task<Player> GetByAuthenticationToken(string token)
        {
            var player = _playerContext.PlayerData.Where(p => p.AuthenticationToken == token);

            return await Load(player);
        }

        private async Task<Player> Load(IQueryable<Player> player)
        {
            return await player.Include(p => p.Inventory)
                .Include(p => p.Badges)
                .Include(p => p.Friendships)
                .FirstOrDefaultAsync();
        }

        public async Task<Player> Create(Player player)
        {
            var entry = await _playerContext.PlayerData.AddAsync(player);

            if (entry.State == EntityState.Added)
                await _playerContext.SaveChangesAsync();

            return player;
        }

        public async Task<Player> Update(Player player)
        {
            var update = _playerContext.PlayerData.Update(player);

            if(update.State == EntityState.Modified)
                await _playerContext.SaveChangesAsync();

            return player;
        }
    }
}