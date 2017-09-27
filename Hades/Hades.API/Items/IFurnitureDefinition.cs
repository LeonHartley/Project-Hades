using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Items.Data;

namespace Hades.API.Items
{
    public interface IFurnitureDefinition
    {
        int Id { get; }
        
        string ItemName { get; }

        bool Sittable { get; }

        bool Walkable { get; }

        bool Stackable { get; }

        StuffDataType DataType { get; }

        ItemType Type { get; }

        double Height { get; }

        int Width { get; }

        int Length { get; }

        string Interaction { get; }

        int StateCount { get; }
    }
}
