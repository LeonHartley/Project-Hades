using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Rooms.Actors
{
    public interface IRoomActors
    { 
        IRoomActor this[string name] { get; }

        IRoomActor this[int virtualId] { get; }

        bool AddActor(IRoomActor actor);

        bool RemoveActor(IRoomActor actor);
    }
}
