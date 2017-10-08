using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.Data.Client
{
    public interface IHadesDataClientProvider
    {
        IHadesDataClient GetClient(string baseUrl, string authorizationToken);
    }

    public class HadesDataClientProvider : IHadesDataClientProvider
    {
        public IHadesDataClient GetClient(string baseUrl, string authorizationToken)
        {
            var dataClient = new HadesDataClient(baseUrl, authorizationToken);

            // Do anything else to it?

            return dataClient;
        }
    }
}
