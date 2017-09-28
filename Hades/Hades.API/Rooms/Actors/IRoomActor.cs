using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Rooms.Tiles;

namespace Hades.API.Rooms.Actors
{
    public interface IRoomActor
    {
        Position Position { get; }
    }
}
