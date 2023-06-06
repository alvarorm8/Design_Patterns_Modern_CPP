#include <iostream>

/*
Here's a very synthetic example for you to try.

You are given a Rectangle protocol and an extension method on it. Try to define a SquareToRectangleAdapter that adapts the Square to the Rectangle interface.
*/

//Here Square is the interface we have and Rectangle is the interface we want to have, so we define SquareToRectangleAdapter to generate a Rectangle through a Square.
//As explained in AdapterVisual.cpp, we have an object (or reference in this case) to the interface we have (Square).
struct Square
{
    int side{ 0 };
    explicit Square(const int side)
        : side(side) {}
};

struct Rectangle
{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const
    {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle
{
    SquareToRectangleAdapter(const Square& square) : 
        m_Square(square)
    {}

    int width() const override 
    {
        return m_Square.side;
    }

    int height() const override
    {
        return m_Square.side;
    }
private:
    const Square& m_Square;
};


int main() {
    Square square{ 10 };
    SquareToRectangleAdapter adapter{ square };

    std::cout << "Rectangle area: " << adapter.area() << std::endl;
	return 0;
}