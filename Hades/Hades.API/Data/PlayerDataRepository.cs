using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Players;

namespace Hades.API.Data
{
    public interface IPlayerDataRepository
    {
        IPlayerData Get(int playerId);

        void Save(IPlayerData data);
    }
}
