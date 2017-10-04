using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;

namespace Hades.Data.Controllers
{
    [Route("core/health")]
    public class HealthController : Controller
    {
        // GET api/health
        [HttpGet]
        public dynamic Get()
        {
            // get health of all servers and return them
            return new
            {
                Status = "OK",
                Services = new[]
                {
                    // Returns "OK" if service responde[serviceName]@[api url]
                    new [] {"OK", "room-service-1@hades/room-service-1" },
                    new [] {"OK", "room-service-2@hades/room-service-2" },
                    new [] {"OK", "room-service-3@hades/room-service-3" }
                }
            };
        }
    }
}
    