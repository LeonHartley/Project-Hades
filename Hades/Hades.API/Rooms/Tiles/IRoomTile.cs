using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Rooms.Actors;
using Hades.API.Rooms.Items;

namespace Hades.API.Rooms.Tiles
{
    public interface IRoomTile
    {
        Position Position { get; }

        List<IRoomItem> Items { get; }

        List<IRoomActor> Actors { get; }

        void Reload();
    }
}