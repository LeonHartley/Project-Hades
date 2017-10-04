using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using Hades.API.Players;
using Hades.API.Players.Data;

namespace Hades.Data.Data.Models
{
    [Table("players")]
    public class PlayerData : IPlayerData
    {
        [Key]
        public int Id { get; set; }

        public string Username { get; set; }

        public string Figure { get; set; }

        public string Motto { get; set; }

        public PlayerGender Gender { get; set; }

        public PlayerData(int id, string username, string figure, string motto, PlayerGender gender)
        {
            Id = id;
            Username = username;
            Figure = figure;
            Motto = motto;
            Gender = gender;
        }
    }
}