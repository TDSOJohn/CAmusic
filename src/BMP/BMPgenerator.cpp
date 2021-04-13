#include "../../include/BMP/BMPgenerator.hpp"

#include <iostream>



BMPgenerator::BMPgenerator():
    size_x(100), size_y(100), mScaling(1)
{
    mBMP = new bitmap_image(size_x, size_y);
    srand(time(NULL));
    generatePalettes();
    choosen = rand()%3;
}


BMPgenerator::BMPgenerator(unsigned int x_in, unsigned int y_in, unsigned int scale_in):
    size_x(x_in), size_y(y_in), mScaling(scale_in)
{
    mBMP = new bitmap_image(size_x, size_y);
    srand(time(NULL));
    generatePalettes();
    choosen = rand()%3;
}


void BMPgenerator::drawData(std::vector<int> const& data_in, unsigned int height)
{
    palette data_out;

    for(int i = 0; i < data_in.size(); i++)
        data_out.push_back(mPalettes[choosen][data_in[i]]);

    drawLine(data_out, height);
}


void BMPgenerator::drawMatrix(std::vector<std::vector<int> > const& data_in)
{

}


void BMPgenerator::saveImage(std::string const& filename)
{
    std::string temp = filename + ".bmp";
    mBMP->save_image(temp);
}


void BMPgenerator::newImage()
{
    if(mBMP != nullptr)
        delete mBMP;
    mBMP = new bitmap_image(size_x, size_y);
}


void BMPgenerator::newImage(unsigned int x_in, unsigned int y_in)
{
    size_x = x_in;
    size_y = y_in;
    newImage();
}


void BMPgenerator::generatePalettes()
{
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});

    mPalettes[0]        ={{0, 0, 0},
                        {32, 41, 62},
                        {81, 18, 26},
                        {232, 181, 130},
                        {227, 137, 113},
                        {225, 115, 100},
                        {255, 255, 255}}; // Changable

    mPalettes[1]        ={{0, 0, 0},
                        {4, 17, 61},
                        {21, 55, 86},
                        {43, 99, 137},
                        {44, 101, 161},
                        {137, 172, 189},
                        {255, 255, 255}}; // Baby Blue

    mPalettes[2]        ={{0, 0, 0},
                        {34, 5, 4},
                        {82, 26, 18},
                        {128, 25, 16},
                        {133, 97, 34},
                        {160, 132, 51},
                        {255, 255, 255}}; // Palermo Fish Market
}


void BMPgenerator::drawLine(std::vector<Pixel> const& data_in, unsigned int height)
{
    //Check if dimensions are at least enough for data writing
    if((data_in.size() * mScaling) <= size_x)
    {
        for(int i = 0; i < data_in.size(); i++)
        {
            for(int x = 0; x < mScaling; x++)
            {
                for(int y = 0; y < mScaling; y++)
                    mBMP->set_pixel((i * mScaling + x),
                                    (height * mScaling + y),
                                    data_in[i].r,
                                    data_in[i].g,
                                    data_in[i].b);
            }
        }
    }
}