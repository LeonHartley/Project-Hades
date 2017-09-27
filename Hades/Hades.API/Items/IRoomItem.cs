using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Items.Data;

namespace Hades.API.Items
{
    public interface IRoomItem
    {
        long Id { get; }

        IStuffData Data { get; }
    }
}
