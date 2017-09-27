using System;
using System.Collections.Generic;
using System.Text;
using Hades.API.Items.Data.Types;

namespace Hades.API.Items.Data
{
    public interface IStuffDataFactory
    {
        IStuffData Create(StuffDataType type, string data);

        string Serialise(IStuffData data);
    }

    public class StuffDataFactory : IStuffDataFactory
    {
        private readonly Dictionary<StuffDataType, Type> _typeMapping = new Dictionary<StuffDataType, Type>();

        public StuffDataFactory()
        {
            _typeMapping[StuffDataType.StringArray] = typeof(StringArrayStuffData);
            _typeMapping[StuffDataType.Highscore] = typeof(HighscoreStuffData);
            _typeMapping[StuffDataType.Empty] = typeof(EmptyStuffData);
            _typeMapping[StuffDataType.Legacy] = typeof(LegacyStuffData);
            _typeMapping[StuffDataType.IntArray] = typeof(IntArrayStuffData);
            _typeMapping[StuffDataType.Map] = typeof(MapStuffData);
        }

        public IStuffData Create(StuffDataType type, string data)
        {
            // Take the type and deserialise the data to an IStuffData object
            throw new NotImplementedException();
        }

        public string Serialise(IStuffData type)
        {
            throw new NotImplementedException();
        }
    }
}
