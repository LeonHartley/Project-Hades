using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Players.Messenger;
using Hades.API.Players.Settings;

namespace Hades.API.Players
{
    /// <summary>
    /// PlayerModel is a representation of all data related to a player
    /// </summary>
    public interface IPlayerModel
    {
        IPlayerData PlayerData { get; set; }

        IPlayerSettings Settings { get; set; }

        List<IPlayerFriendship> MessengerFriendships { get; set; }
    }
}
