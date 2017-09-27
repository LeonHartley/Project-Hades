using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Players.Inventory
{
    public interface IPlayerInventory
    {
        IPlayer Player { get; }

        Dictionary<int, IInventoryItem> InventoryItems { get; }
    }
}
