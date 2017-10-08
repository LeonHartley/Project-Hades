using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using Coerce.Commons.Logging;
using Coerce.Commons.Logging.Appenders;
using Coerce.Networking.Api;
using Coerce.Networking.Core;
using Hades.Data.Client;
using Hades.Data.Models.Players;
using Hades.Peer.Networking;
using Microsoft.Extensions.DependencyInjection;
using StructureMap;

namespace Hades.Peer
{
    class Program
    {
        public static void Main(string[] args)
        {
            var container = new Container();

            container.Configure(ConfigureServices);

            var peerServer = container.GetInstance<IHadesPeerServer>();
            peerServer.Start();
        }

        public static void ConfigureServices(ConfigurationExpression serviceConfig)
        {
            var loggerService = new LoggerService();

            List<LoggerAppender> appenders = new List<LoggerAppender>();
            appenders.Add(new ConsoleAppender());

            loggerService.Config.Appenders = appenders;
            LoggerService.Instance = loggerService;

            // Coerce.NET registrations
            serviceConfig.For<INetworkingService>().Use<CoreNetworkingService>().Singleton();
            serviceConfig.For<IHadesPeerServer>().Use<HadesPeerServer>().Singleton();
        }
    }
}
