using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Rooms.Tiles
{
    public interface IRoomMap
    {
        IRoomTile this[Position position] { get; }
        
        void Reload();
    }
}
