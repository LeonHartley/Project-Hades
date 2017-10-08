using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Hades.API.Players;
using Hades.API.Players.Data;
using Hades.Data.Context;
using Hades.Data.Models.Players;
using Hades.Data.Models;
using Hades.Data.Repositories;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace Hades.Data.Controllers.Players
{
    [Route("data/players")]
    public class PlayerController : Controller
    {
        private readonly IPlayerRepository _playerRepository;

        public PlayerController(IPlayerRepository playerRepository)
        {
            _playerRepository = playerRepository;
        }

        // GET data/players
        [HttpGet]
        public dynamic Get()
        {
            // Grab status object from redis cache
            return new
            {
                Online = 0,
                Total = 1
            };
        }

        // GET data/players/{id}
        [HttpGet("{id}")]
        public async Task<IActionResult> Get(int id)
        {
            var player = await _playerRepository.Get(id);

            if (player == null)
            {
                return NotFound();
            }

            return Ok(player);
        }

        [HttpPost("authenticate/")]
        public async Task<IActionResult> Authenticate([FromBody] dynamic request)
        {
            var player = await _playerRepository.Authenticate((string) request.SsoToken);

            if (player == null)
            {
                return NotFound();
            }

            return Ok(player);
        }

        [HttpPost]
        public async Task<IActionResult> Create([FromBody] Player player)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(player);
            }

            var created = await _playerRepository.Create(player);

            return Ok(created);
        }

        // PUT data/players/{id}
        [HttpPut("{id}")]
        public async Task<IActionResult> Save([FromBody] Player player)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            await _playerRepository.Update(player);

            // Save the player object into the chosen data store
            return Ok();
        }
    }
}