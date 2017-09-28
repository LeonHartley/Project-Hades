using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Players.Inventory.Items;

namespace Hades.API.Players.Inventory
{
    public interface IPlayerInventory
    {
        IPlayer Player { get; }

        Dictionary<int, IInventoryItem> InventoryItems { get; }

        void Add(IInventoryItem item);

        void Remove(IInventoryItem item);
    }
}
