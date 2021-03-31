#include "../../headers/BMP/BMPgenerator.hpp"

#include <iostream>


BMPgenerator::BMPgenerator():
    size_x(100), size_y(100), mScaling(1), mBMP(size_x, size_y)
{
    srand(time(NULL));
    generatePalettes();
    choosen = rand()%3;
}


BMPgenerator::BMPgenerator(unsigned int x_in, unsigned int y_in, unsigned int scale_in):
    size_x(x_in), size_y(y_in), mScaling(scale_in), mBMP(size_x, size_y)
{
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
    mBMP.save_image(filename);
}


void BMPgenerator::generatePalettes()
{
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});

    mPalettes[0]        ={{0, 0, 0},
                        {81, 18, 26},
                        {32, 41, 62},
                        {232, 181, 130},
                        {227, 137, 113},
                        {225, 115, 100}}; // Changable

    mPalettes[1]        ={{0, 0, 0},
                        {4, 17, 61},
                        {21, 55, 86},
                        {44, 101, 161},
                        {137, 172, 189},
                        {43, 99, 137}}; // Baby Blue

    mPalettes[2]        ={{34, 5, 4},
                        {160, 132, 51},
                        {133, 97, 34},
                        {82, 26, 18},
                        {128, 25, 16}}; // Palermo Fish Market
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
                    mBMP.set_pixel( (i * mScaling + x),
                                    (height * mScaling + y),
                                    data_in[i].r,
                                    data_in[i].g,
                                    data_in[i].b);
            }
        }
    }
}
