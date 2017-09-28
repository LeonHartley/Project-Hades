using Hades.API.Items.Data;
using Hades.API.Rooms.Tiles;

namespace Hades.API.Rooms.Items
{
    public interface IRoomItem
    {
        long Id { get; }

        int State { get; set; }

        IStuffData Data { get; }

        Position Position { get; }
    }
}
