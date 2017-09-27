using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Hades.API.Players;

namespace Hades.API.Services.Players
{
    public interface IPlayerService : IService
    {
        /// <summary>
        /// Asynchronously authenticates a player
        /// </summary>
        /// <param name="ssoTicket">The ticket generated on the client</param>
        /// <returns>Player object</returns>
        Task<IPlayer> AuthenticatePlayer(string ssoTicket);
    }
}
