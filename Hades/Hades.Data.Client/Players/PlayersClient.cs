using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Hades.Data.Models.Players;

namespace Hades.Data.Client.Players
{
    public interface IPlayersClient
    {
        Task<Player> Get(int id);
    }

    public class PlayersClient : IPlayersClient
    {
        private readonly IHadesDataClient _baseClient;

        public PlayersClient(IHadesDataClient baseClient)
        {
            _baseClient = baseClient;
        }

        public async Task<Player> Get(int id)
        {
            _baseClient.Endpoint = string.Format("/data/players/{0}", id);
            _baseClient.Method = HttpMethod.Get;
            _baseClient.Payload = "";
            
            return await _baseClient.Get<Player>();
        }
    }
}
