using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Players.Wardrobe
{
    public interface IPlayerWardrobe
    {
        List<string> Clothing { get; }

        void AddClothing(string clothingName);
    }
}
