#pragma once

#include <vector>

namespace DutchFeud::Common::Data
{
    class Tile
    {
        public:

        enum class Shape : int
        {
            Undefined = 0,
            Cheese,
            Windmill,
            Tulip,
            Clogs,
            Bicycle,
            Lion,
            ShapeCount
        };
        typedef std::underlying_type< Tile::Shape >::type TShapeUnderlying;

        enum class Color : int
        {
            Undefined = 0,
            Red,
            Green,
            Yellow,
            Orange,
            Blue,
            Purple,
            ColorCount       
        };
        typedef std::underlying_type< Tile::Color >::type TColorUnderlying;

        private:
        Shape _shape;
        Color _color;

        public:
        Tile();
        Tile( Shape shape, Color color );
        
        bool operator==( const Tile & rhs ) const;

        bool operator!=( const Tile & rhs ) const;

        const Shape & GetShape() const;

        const Color & GetColor() const;
    };
}