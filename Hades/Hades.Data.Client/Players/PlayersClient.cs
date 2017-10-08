using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Hades.Data.Models.Players;
using Newtonsoft.Json;

namespace Hades.Data.Client.Players
{
    public interface IPlayersClient
    {
        Task<Player> Get(int id);

        Task<Player> Authenticate(string ssoToken);

        Task<Player> Update(Player player);

        Task<Player> Create(Player player);
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

        public async Task<Player> Authenticate(string ssoToken)
        {
            _baseClient.Endpoint = "/data/players/authenticate";
            _baseClient.Method = HttpMethod.Post;
            _baseClient.Payload = ssoToken;

            return await _baseClient.Get<Player>();
        }

        public async Task<Player> Update(Player player)
        {
            _baseClient.Endpoint = string.Format("/data/players/{0}", player.Id);
            _baseClient.Method = HttpMethod.Put;
            _baseClient.Payload = JsonConvert.SerializeObject(player);

            return await _baseClient.Get<Player>();
        }

        public async Task<Player> Create(Player player)
        {
            _baseClient.Endpoint = "/data/players";
            _baseClient.Method = HttpMethod.Post;
            _baseClient.Payload = JsonConvert.SerializeObject(player);

            return await _baseClient.Get<Player>();
        }
    }
}