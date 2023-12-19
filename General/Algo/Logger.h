#pragma once

#include <string>

namespace DutchFeud::General::Algo
{    
    class Logger
    {
    public:
        enum class LogLevel
        {
            Debug,
            Error,
            Fatal,
            Info,
            Trace,
            Warning,
        };

    public:
        void Log( LogLevel logLevel, const std::string & message );
        void Log( LogLevel logLevel, const char * message );
        void Debug( const char * message );
        void Debug( const std::string & message );
        void Error( const char * message );
        void Error( const std::string & message );
        void Fatal( const char * message );
        void Fatal( const std::string & message );
        void Trace( const char * message );
        void Trace( const std::string & message );
        void Warning( const char * message );
        void Warning( const std::string & message );
    private:
        const std::string & Convert( LogLevel logLevel ) const;        
        std::string GetTimeStamp() const;
        void ExecuteLog( std::string );
    };

    class LogManager
    {
    public:
        static Logger & GetCurrentClassLogger();
    };
}