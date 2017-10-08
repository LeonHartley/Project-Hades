using System;
using System.Collections.Generic;
using System.Text;
using Coerce.Networking.Api.Channels;
using Hades.Peer.Networking.Channels.Handlers;

namespace Hades.Peer.Networking.Channels
{
    public class ChannelInitialiser : IChannelInitialiser
    {
        public void InitialiseChannel(Channel channel)
        {
            channel.Pipeline.AddLast("Hades", new HadesChannelHandler());
        }
    }
}
