#include "GetServerVersion.h"

#include "Config.h"

using namespace DutchFeud;
using namespace DutchFeud::Server;
using namespace DutchFeud::Server::Algo;

const std::string &
GetServerVersion::Execute() const
{
    static const std::string version = VERSION_STRING;
    return version;
}
