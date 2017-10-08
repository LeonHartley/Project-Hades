using System;
using System.Collections.Generic;
using System.Text;
using Coerce.Commons.Logging;
using Coerce.Networking.Api;
using Coerce.Networking.Api.Channels;
using Hades.Peer.Networking.Channels;

namespace Hades.Peer.Networking
{
    public interface IHadesPeerServer
    {
        void Start();
    }

    public class HadesPeerServer : IHadesPeerServer
    {
        private readonly Logger _log = LoggerService.Instance.Create(nameof(HadesPeerServer));

        private readonly INetworkingService _networkingService;

        public HadesPeerServer(INetworkingService networkingService)
        {
            _networkingService = networkingService;
        }

        public void Start()
        {
            _networkingService.Configure(new ChannelInitialiser());

            _networkingService.Start("0.0.0.0", 3000, (ctx) =>
            {
                _log.Info("Started TCP server");

                while (true)
                {
                    string command = Console.ReadLine();

                    // Command handler or something?
                }
            });
        }
    }
}
