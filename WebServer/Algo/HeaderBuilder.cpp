#include "HeaderBuilder.h"

using namespace DutchFeud;
using namespace DutchFeud::WebServer;
using namespace DutchFeud::WebServer::Algo;

HeaderBuilder::HeaderBuilder( int statusCode )
{
    _headerStream << HeaderBuilder::HTTP_VERSION_STRING << " " << statusCode << " " << GetStatusMessage(statusCode) << "\r\n";
}

void
HeaderBuilder::SetContentLength( size_t contentLength )
{
    SetHeaderOption( HTTP_CONTENT_LENGTH_STRING, contentLength ); 
}

void 
HeaderBuilder::SetContentType( const char* contentType )
{
    SetHeaderOption( HTTP_CONTENT_TYPE_STRING, contentType );
}

std::string
HeaderBuilder::BuildHeader()
{
    _headerStream << "\r\n";
    return _headerStream.str();    
}

std::string 
HeaderBuilder::GetStatusMessage( int statusCode ) 
{
    switch (statusCode) {
        case 200:
            return "OK";
        case 404:
            return "Not Found";
        default:
            return "Unknown Status";
    }
}

void
HeaderBuilder::SetHeaderOption( const std::string & option, const std::string & value )
{
    _headerStream << option << ": " << value << "\r\n";
}

void
HeaderBuilder::SetHeaderOption( const std::string & option, size_t value )
{
    _headerStream << option << ": " << value << "\r\n";
}

