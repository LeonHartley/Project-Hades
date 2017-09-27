using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Players.Data;

namespace Hades.API.Players
{
    public interface IPlayerData
    {
        int Id { get; }

        string Username { get; set;  }

        string Figure { get; set; }

        string Motto { get; set; }
        
        PlayerGender Gender { get; set; }
    }
}
