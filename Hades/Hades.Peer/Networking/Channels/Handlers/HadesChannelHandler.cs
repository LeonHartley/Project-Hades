using System;
using System.Collections.Generic;
using System.Text;
using Coerce.Commons.Logging;
using Coerce.Networking.Api.Buffer;
using Coerce.Networking.Api.Channels;
using Coerce.Networking.Api.Context.Channels;
using Coerce.Networking.Api.Pipeline.Handlers;

namespace Hades.Peer.Networking.Channels.Handlers
{
    public class HadesChannelHandler : IChannelHandler
    {
        private static Logger _log = LoggerService.Instance.Create(nameof(HadesChannelHandler));

        public void OnChannelConnected(ChannelHandlerContext context)
        {
            _log.Trace("Channel connected");
        }

        public void OnChannelDisconnected(ChannelHandlerContext context)
        {
            _log.Trace("Channel disconnected");
        }

        public void OnChannelDataReceived(IBuffer buffer, ChannelHandlerContext context)
        {
            throw new NotImplementedException();
        }

        public void OnChannelEvent(ChannelEvent triggeredEvent, ChannelHandlerContext context)
        {
            throw new NotImplementedException();
        }

        public void OnChannelException(Exception exception, ChannelHandlerContext context)
        {
            throw new NotImplementedException();
        }
    }
}
