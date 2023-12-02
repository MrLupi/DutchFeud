#pragma once

namespace DutchFeud::Common::Data
{
    struct PlayFieldLocation
    {
        public:
        unsigned int X;
        unsigned int Y;

        PlayFieldLocation( unsigned int x, unsigned int y );

        bool operator==( const PlayFieldLocation & rhs ) const;
        
        bool operator!=( const PlayFieldLocation & rhs ) const;
    };
}