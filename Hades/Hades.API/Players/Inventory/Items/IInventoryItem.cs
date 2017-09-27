using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Items;
using Hades.API.Items.Data;

namespace Hades.API.Players.Inventory.Items
{
    public interface IInventoryItem
    {
        long Id { get; }

        int BaseItemId { get; }

        IStuffData Data { get; }
    }
}
