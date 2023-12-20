#pragma once

#include <string>
#include <sstream>

namespace DutchFeud::WebServer::Algo
{
    class HeaderBuilder
    {
    private:
        const char* HTTP_VERSION_STRING = "HTTP/1.1";
        const char* HTTP_CONTENT_TYPE_STRING = "Content-Type";
        const char* HTTP_CONTENT_LENGTH_STRING = "Content-Length";

        std::ostringstream _headerStream;
    public:
        HeaderBuilder( int statusCode );
        void SetContentLength( size_t contentLength );
        void SetContentType( const char* contentType );
        std::string BuildHeader();
    private:
        static std::string GetStatusMessage( int statusCode );
        void SetHeaderOption( const std::string & option, const std::string & value );
        void SetHeaderOption( const std::string & option, size_t value );
    };
}