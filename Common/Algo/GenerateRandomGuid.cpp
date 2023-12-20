#include "GenerateRandomGuid.h"

#include <uuid/uuid.h>

using namespace DutchFeud;
using namespace DutchFeud::Common;
using namespace DutchFeud::Common::Algo;

std::string
GenerateRandomGuid::operator()()
{
    char uuidString[UUID_STR_LEN];
    uuid_t uuid;
    
    uuid_generate_random( uuid );
    uuid_unparse_lower( uuid, uuidString );
    
    return std::string( uuidString );    
}