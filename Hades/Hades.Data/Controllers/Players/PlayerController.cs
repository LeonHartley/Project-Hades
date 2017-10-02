using Hades.API.Data;
using Hades.API.Players;
using Hades.API.Players.Data;
using Hades.Data.Data.Models;
using Microsoft.AspNetCore.Mvc;

namespace Hades.Data.Controllers.Players
{
    [Route("data/players")]
    public class PlayerController : Controller
    {
        // GET data/players
        [HttpGet]
        public dynamic Get()
        {
            // Grab status object from redis cache
            return new
            {
                Online = 1,
                Total = 10
            };
        }

        // GET data/players/{id}
        [HttpGet("{id}")]
        public IPlayerData Get(int id)
        {
            // If there's an object in the redis cache, return it rather than fetching it from the database


            // Grab the player object from the chosen data store
            return new PlayerData(id, "Leon", "figure", "motto", PlayerGender.Male);
        }
        
        // PUT data/players/{id}
        [HttpPut("{id}")]
        public string Save([FromBody] PlayerData player)
        {
            // Save the player object into the chosen data store
            return "OK";
        }
    }
}
