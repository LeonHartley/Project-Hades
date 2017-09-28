using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Rooms.Actors;

namespace Hades.API.Rooms
{
    public interface IRoom
    {
        int Id { get; }

        IRoomData Data { get; }

        IRoomActors Actors { get; }
    }
}
