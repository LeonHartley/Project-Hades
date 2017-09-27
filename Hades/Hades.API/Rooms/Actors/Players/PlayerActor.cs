using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Players;

namespace Hades.API.Rooms.Actors.Players
{
    public interface IPlayerActor : IRoomActor
    {
        int Id { get; }

        IPlayer Player { get; }
    }
}
