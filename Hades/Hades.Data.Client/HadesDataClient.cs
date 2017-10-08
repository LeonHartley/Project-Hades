using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Net.Http;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;
using Hades.Data.Client.Players;
using Microsoft.EntityFrameworkCore.Migrations.Operations;
using Newtonsoft.Json;
using Remotion.Linq.Clauses;

namespace Hades.Data.Client
{
    public interface IHadesDataClient
    {
        string BaseUrl { get; }

        string Endpoint { get; set; }

        HttpMethod Method { get; set; }

        string Payload { get; set; }

        Task<T> Get<T>();

        IPlayersClient Players { get; }
    }

    public class HadesDataClient : IHadesDataClient
    {
        private IPlayersClient _playersClient;

        private readonly string _authorizationToken;

        public HadesDataClient(string baseUrl, string authorizationToken)
        {
            _authorizationToken = authorizationToken;

            BaseUrl = baseUrl;
        }

        public string BaseUrl { get; }

        public string Endpoint { get; set; }

        public HttpMethod Method { get; set; }

        public string Payload { get; set; }

        private HttpRequestMessage CreateRequest()
        {
            HttpRequestMessage request = new HttpRequestMessage(Method, BaseUrl + Endpoint);

            request.Headers.Add("X-Hades-Authorization", _authorizationToken);
            request.Content = new StringContent(Payload, Encoding.UTF8, "application/json");

            return request;
        }

        public async Task<T> Get<T>()
        {
            using (HttpClient client = new HttpClient())
            {
                var result = await client.SendAsync(CreateRequest());
                var data = await result.Content.ReadAsStringAsync();

                return JsonConvert.DeserializeObject<T>(data);
            }
        }

        public IPlayersClient Players => _playersClient ?? (_playersClient = new PlayersClient(this));
    }
}