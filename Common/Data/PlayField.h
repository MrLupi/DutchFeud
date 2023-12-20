#pragma once

#include <array>

#include "Common/Data/PlayFieldLocation.h"
#include "Common/Data/PlayFieldSquare.h"

namespace DutchFeud::Common::Data
{
    class PlayField
    {        
        public:
        
        enum class Layout
        {
            Default,
            Random,
            Empty
        };

        static const unsigned int PlayFieldSize = 15;
        const unsigned int RandomVariantACount = 20;
        const unsigned int RandomVariantBCount = 12;

        PlayFieldSquare _squares[PlayFieldSize][PlayFieldSize];

        public:
        PlayField( Layout layout );

        unsigned int GetMultiplier( const PlayFieldLocation & location ) const;


        private:
        void InitializeDefaultPlayField();

        void InitializeRandomPlayField();

        PlayFieldSquare & GetSquare( const PlayFieldLocation & location );
        
        const PlayFieldSquare & GetSquareConst( const PlayFieldLocation & location ) const;
        
        void SetRandomMultipliers( unsigned int value, unsigned int count );
    };
}