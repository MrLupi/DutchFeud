#include "Logger.h"

#include <ctime>
#include <iostream>

using namespace DutchFeud;
using namespace DutchFeud::General;
using namespace DutchFeud::General::Algo;

void 
Logger::Debug( const char * message )
{
    Log( LogLevel::Debug, message );
}

void 
Logger::Debug( const std::string & message )
{
    Log( LogLevel::Debug, message );
}

void 
Logger::Error( const char * message )
{
    Log( LogLevel::Error, message );
}

void 
Logger::Error( const std::string & message )
{
    Log( LogLevel::Error, message );
}

void 
Logger::Fatal( const char * message )
{
    Log( LogLevel::Fatal, message );
}

void 
Logger::Fatal( const std::string & message )
{
    Log( LogLevel::Fatal, message );
}

void 
Logger::Info( const char * message )
{
    Log( LogLevel::Info, message );
}

void 
Logger::Info( const std::string & message )
{
    Log( LogLevel::Info, message );
}

void 
Logger::Trace( const char * message )
{
    Log( LogLevel::Trace, message );
}

void 
Logger::Trace( const std::string & message )
{
    Log( LogLevel::Trace, message );
}

void 
Logger::Warning( const char * message )
{
    Log( LogLevel::Warning, message );
}

void 
Logger::Warning( const std::string & message )
{
    Log( LogLevel::Warning, message );
}

void
Logger::Log( LogLevel logLevel, const std::string & message )
{
    Log( logLevel, message.c_str() );
}

void
Logger::Log( LogLevel logLevel, const char * message )
{
    const auto timeStampStr = GetTimeStamp();
    const auto & logLevelStr = Convert( logLevel );

    auto logEntry = timeStampStr + " [" + logLevelStr + "] " + message;

    ExecuteLog( logEntry );
}


const std::string &
Logger::Convert( Logger::LogLevel logLevel ) const
{
    static const std::string debug = "Debug";
    static const std::string error = "Error";
    static const std::string fatal = "Fatal";
    static const std::string info = "Info";
    static const std::string trace = "Trace";
    static const std::string unexpected = "Unexpected log type";
    static const std::string warning = "Warning";

    switch ( logLevel )
    {
    case Logger::LogLevel::Debug :
        return debug;
    case Logger::LogLevel::Error :
        return error;
    case Logger::LogLevel::Fatal :
        return fatal;    
    case Logger::LogLevel::Info :
        return info;
    case Logger::LogLevel::Trace :
        return trace;
    case Logger::LogLevel::Warning :
        return warning;
    default:
        // ToDo assertion here
        return unexpected;
    }
}

std::string
Logger::GetTimeStamp() const
{
    const auto now = std::time(nullptr);
    char timestamp[20];
    std::strftime( timestamp, sizeof( timestamp ), "%Y-%m-%d %H:%M:%S", std::localtime( & now ) );
    return timestamp;
}

void
Logger::ExecuteLog( std::string log )
{
    std::cout << log << std::endl;
}

Logger & 
LogManager::GetCurrentClassLogger()
{
    static Logger logger = Logger();
    return logger;
}
