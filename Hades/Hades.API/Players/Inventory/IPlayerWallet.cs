using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Players.Inventory
{
    public interface IPlayerWallet
    {
        int Credits { get; }

        int VipPoints { get; }

        int ActivityPoints { get; }

        void IncreaseCredits(int amount);

        void IncreaseVipPoints(int amount);

        void IncreaseActivityPoints(int amount);
    }
}
