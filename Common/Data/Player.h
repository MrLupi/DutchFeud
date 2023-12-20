#pragma once

#include <mutex>
#include <string>
#include <uuid/uuid.h>


namespace DutchFeud::Common::Data
{
    class Player
    {
        private:
        std::string _guid;
        std::wstring _name;
        std::mutex _lock;

        public:
        Player();

        const std::string & GetGuid() const;
        const std::wstring & GetName() const;
    };
}