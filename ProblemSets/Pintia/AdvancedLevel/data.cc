#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

class myInt {
   public:
    int operator[]( std::vector<int>::iterator const& it ) const {
        return *( val + it );
    }
    myInt( int v ) : val( v ) {}
    int val = 0;
};

int main() {
    constexpr std::size_t xy = 4;
    using Cell = std::array<unsigned char, 8>;
    std::array<Cell, xy * xy> board;
    board.fill( { 0xE2, 0x96, 0x84, 0xE2, 0x96, 0x80, 0, 0 } );  // "▄▀";
    for ( std::size_t count{}; Cell c : board )
        std::cout << c.data() << ( ( ++count % xy ) ? "" : "\n" );
    std::cout << "ABC"[2] << "-" << 2 ["ABC"] << std::endl;
    std::vector<int> list{ 1, 2, 3 };
    std::cout << list.begin()[2] << myInt( 2 )[list.begin()] << std::endl;
    auto abs = []( int num ) {
        std::cout << "From inner abs: " << ( ::abs( num ) ) << std::endl;
    };
    abs( -1 );
    ::abs( -1 );
}