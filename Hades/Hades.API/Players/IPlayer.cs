using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Players.Inventory;
using Hades.API.Players.Messenger;
using Hades.API.Players.Settings;
using Hades.API.Players.Wardrobe;

namespace Hades.API.Players
{
    public interface IPlayer
    {
        IPlayerWallet Wallet { get; set; }

        IPlayerInventory Inventory { get; }

        IPlayerMessenger Messenger { get; }

        IPlayerWardrobe Wardrobe { get; }

        IPlayerSettings Settings { get; }
    }
}
