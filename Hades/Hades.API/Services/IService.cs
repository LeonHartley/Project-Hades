namespace Hades.API.Services
{
    public interface IService
    {
        /// <summary>
        /// Reloads all cached data the service holds
        /// </summary>
        void Reload();
    }
}
