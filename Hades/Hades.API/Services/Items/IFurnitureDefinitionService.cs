using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Items;

namespace Hades.API.Services.Items
{
    public interface IFurnitureDefinitionService : IService
    {
        /// <summary>
        /// Gets the furniture definition of the chosen item
        /// </summary>
        /// <param name="id">The ID of the definition</param>
        /// <returns>Furniture definition object</returns>
        IFurnitureDefinition GetDefinition(int id);
    }
}
