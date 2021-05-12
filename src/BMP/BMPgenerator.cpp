#include "../../include/BMP/BMPgenerator.hpp"

#include <iostream>



BMPgenerator::BMPgenerator(unsigned int x_in, unsigned int y_in, int scale_in):
    size_x(x_in), size_y(y_in), mScaling(scale_in), choosen(0)
{
    mBMP = new bitmap_image(size_x, size_y);
    srand(time(NULL));
    generatePalettes();
}


void BMPgenerator::drawData(std::vector<int> const& data_in, unsigned int height, unsigned int states_in)
{
    palette data_out;
    //  choosen == 0 => greyscale
    if(choosen != 0)
    {
        for(int i = 0; i < data_in.size(); i++)
            data_out.push_back(mPalettes[choosen][data_in[i]]);
    } else
    {
        for(auto& i : data_in)
            data_out.push_back(Pixel(   (255 / (states_in - 1) * i),
                                        (255 / (states_in - 1) * i),
                                        (255 / (states_in - 1) * i)));
    }

    drawLine(data_out, height);
}


void BMPgenerator::drawMatrix(std::vector<std::vector<int> > const& data_in)
{

}


void BMPgenerator::saveFile(std::string const& filename)
{
    std::string temp = "results/" + filename + "_p" + char(choosen + 48) + ".bmp";
    mBMP->save_image(temp);
}


void BMPgenerator::newFile()
{
    if(mBMP != nullptr)
        delete mBMP;
    mBMP = new bitmap_image(size_x, size_y);
}


void BMPgenerator::newFile(const int palette_in)
{
    choosen = palette_in;
}


void BMPgenerator::newFile(unsigned int x_in, unsigned int y_in)
{
    size_x = x_in;
    size_y = y_in;
    newFile();
}


void BMPgenerator::generatePalettes()
{
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});

    mPalettes[1]        ={{0, 0, 0},
                        {32, 41, 62},
                        {81, 18, 26},
                        {232, 181, 130},
                        {227, 137, 113},
                        {225, 115, 100},
                        {255, 255, 255}}; // Changable

    mPalettes[2]        ={{0, 0, 0},
                        {4, 17, 61},
                        {21, 55, 86},
                        {43, 99, 137},
                        {44, 101, 161},
                        {137, 172, 189},
                        {255, 255, 255}}; // Baby Blue

    mPalettes[3]        ={{0, 0, 0},
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
