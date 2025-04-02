#include <bits/stdc++.h>
using namespace std;
class Rectangle {
   protected:
    int width, height;

   public:
    Rectangle( const int width, const int height ) : width{ width }, height{ height } {}
    int get_width() { return width; }
    virtual void set_width( const int width ) { this->width = width; }
    int get_height() { return height; }
    virtual void set_height( const int height ) { this->height = height; }
    int area() const { return width * height; }
};

class Square : public Rectangle {
   public:
    Square( const int size ) : Rectangle( size, size ) {}
    void set_width( const int width ) override {
        this->width = height = width;
    }
    void set_height( const int height ) override {
        this->height = width = height;
    }
};

// Derived class's behavior must not change base class's property.
void process( Rectangle& r ) {
    int w = r.get_width();
    r.set_height( 10 );
    cout << "Expected area = " << ( w * 10 ) << ", got " << r.area() << endl;
}

int main() {
    Square s{ 5 };
    process( s );
    return 0;
}