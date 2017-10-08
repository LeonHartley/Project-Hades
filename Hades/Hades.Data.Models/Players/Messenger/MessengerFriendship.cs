using System.ComponentModel.DataAnnotations;
using Hades.API.Players.Messenger;

namespace Hades.Data.Models.Players.Messenger
{
    public class PlayerFriendship : IPlayerFriendship
    {
        [Key]
        public int Id { get; set; }

        public int PlayerId { get; set; }

        public int FriendId { get; set; }
    }
}
