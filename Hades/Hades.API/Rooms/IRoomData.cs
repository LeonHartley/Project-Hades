using System;
using System.Collections.Generic;
using System.Text;

namespace Hades.API.Rooms
{
    public interface IRoomData
    {
        int Id { get; }

        string Name { get; set; }
        
        string Description { get; }

        int PlayerId { get; }

        int GroupId { get; set; }
    }
}
