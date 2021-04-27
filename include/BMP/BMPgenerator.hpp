#ifndef bmpgenerator_hpp
#define bmpgenerator_hpp


#include <vector>

#include "bitmap_image.hpp"



struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Pixel(unsigned char r_in, unsigned char g_in, unsigned char b_in):
        r(r_in), g(g_in), b(b_in) {};
};


class BMPgenerator
{
public:
    typedef std::vector<Pixel> palette;

                            /// Default: 100x100 image, scaling = 1
                            BMPgenerator();
                            BMPgenerator(unsigned int x_in, unsigned int y_in, unsigned int scale_in = 2);

    void                    drawData(std::vector<int> const& data_in, unsigned int height, unsigned int states_in);
    void                    drawMatrix(std::vector<std::vector<int> > const& data_in);

    void                    saveFile(std::string const& filename);

    /// Create new bitmap image using size_x and size_y stored values
    void                    newFile();
    /// Create new bitmap image, pass palette number as parameter (0 for grey scale, 1,2,3 for colors)
    void                    newFile(unsigned int palette_in);
    /// Create new bitmap image, pass x and y sizes as parameters
    void                    newFile(unsigned int x_in, unsigned int y_in);

private:
    unsigned int            size_x, size_y;
    unsigned int            mScaling;
    bitmap_image*           mBMP;

    std::vector<std::vector<Pixel> >
                            mPalettes;
    unsigned int            choosen;

private:
    void                    generatePalettes();
    void                    drawLine(std::vector<Pixel> const& data_in, unsigned int height);
};


#endif //bmpgenerator_hpp
