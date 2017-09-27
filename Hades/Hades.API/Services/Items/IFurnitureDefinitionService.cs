using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Items;

namespace Hades.API.Services.Items
{
    public interface IFurnitureDefinitionService : IService
    {
        IFurnitureDefinition GetDefinition(int id);
    }
}
