#include <iostream>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

/*
* A virtual proxy gives you the appearance of working with the same object that you're used to work with even though the object might not even been created.
*/

struct Image
{
    virtual ~Image() = default;
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const string& filename)
    {
        cout << "Loading image from " << filename << endl;
    }

    void draw() override
    {
        cout << "Drawing image" << endl;
    }
};

struct LazyBitmap : Image //proxy class which does not load the image until it is going to be printed
{
    LazyBitmap(const string& filename) : filename(filename) {}
    ~LazyBitmap() { delete bmp; }
    void draw() override
    {
        if (!bmp) //if bmp has not been initialized, the image is loaded
            bmp = new Bitmap(filename);
        bmp->draw();
    }

private:
    Bitmap* bmp{ nullptr };
    string filename;
};

void draw_image(Image& img)
{
    cout << "About to draw the image" << endl;
    img.draw();
    cout << "Done drawing the image" << endl;
}

void virtual_proxy()
{
    LazyBitmap img{ "pokemon.png" };
    draw_image(img); // loaded whether the bitmap is loaded or not
    draw_image(img);
}

int main()
{
    virtual_proxy();

    getchar();
    return 0;
}