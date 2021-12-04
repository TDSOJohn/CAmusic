#include "../../include/BMP/BMPgenerator.hpp"


BMPgenerator::BMPgenerator(int x_in, int y_in, int scale_in):
    size_x(x_in * scale_in), size_y(y_in * scale_in), mScaling(scale_in), choosen(0)
{
    mBMP = new bitmap_image(size_x, size_y);
    srand(time(NULL));
    generatePalettes();
}

void BMPgenerator::drawData(std::vector<int> const& data_in, int height, int states_in)
{
    //Check if dimensions are at least enough for data writing
    if(((data_in.size() * mScaling) <= size_x) && (height <= size_y))
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

void BMPgenerator::newFile(int x_in, int y_in, int scaling)
{
    if(scaling)
        mScaling = scaling;

    size_x = x_in * mScaling;
    size_y = y_in * mScaling;
    newFile();
}

void BMPgenerator::generatePalettes()
{
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});
    mPalettes.push_back({{0, 0, 0}});

    mPalettes[1]        ={{0, 0, 0},
                        {0xE6, 0x39, 0x46},
                        {0xF1, 0xFA, 0xEE},
                        {0xA8, 0xDA, 0xDC},
                        {0x45, 0x7B, 0x9D},
                        {0x1D, 0x35, 0x57},
                        {0xFF, 0xFF, 0xFF}};

    mPalettes[2]        ={{0, 0, 0},
                        {0x8E, 0xCA, 0xE6},
                        {0x21, 0x9E, 0xBC},
                        {0x02, 0x30, 0x47},
                        {0xFF, 0xB7, 0x03},
                        {0xFB, 0x85, 0x00},
                        {0xFF, 0xFF, 0xFF}};

    mPalettes[3]        ={{0, 0, 0},
                        {0x28, 0x3D, 0x3B},
                        {0x19, 0x72, 0x78},
                        {0xED, 0xDD, 0xD4},
                        {0xC4, 0x45, 0x36},
                        {0x77, 0x2E, 0x25},
                        {0xFF, 0xFF, 0xFF}};
}

void BMPgenerator::drawLine(std::vector<Pixel> const& data_in, int height)
{
    for(int i = 0; i < data_in.size(); i++)
    {
        for(int x = 0; x < mScaling; x++)
        {
            for(int y = 0; y < mScaling; y++)
                mBMP->set_pixel(std::min((i * mScaling + x), size_x),
                                std::min((height * mScaling + y), size_y),
                                data_in[i].r,
                                data_in[i].g,
                                data_in[i].b);
        }
    }
}
