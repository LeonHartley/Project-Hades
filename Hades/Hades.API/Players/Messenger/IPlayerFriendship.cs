using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Players.Messenger
{
    public interface IPlayerFriendship
    {
        int PlayerId { get; set; }

        int FriendId { get; set; }
    }
}
