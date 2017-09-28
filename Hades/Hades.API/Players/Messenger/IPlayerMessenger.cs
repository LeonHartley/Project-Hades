using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Players.Messenger
{
    public interface IPlayerMessenger
    {
        List<int> Friends { get; }

        void InviteFriends(string message);

        void Chat(string message, int friendId);

        void AddFriend(int friendId);

        void RemoveFriend(int friendId);
    }
}
