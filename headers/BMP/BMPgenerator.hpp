#ifndef bmpgenerator_hpp
#define bmpgenerator_hpp


#include <vector>

#include "bitmap_image.hpp"



struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};


class BMPgenerator
{
public:
    typedef std::vector<Pixel> palette;

                            //  Default: 100x100 image, scaling = 1
                            BMPgenerator();
                            BMPgenerator(unsigned int x_in, unsigned int y_in, unsigned int scale_in);

    void                    drawData(std::vector<int> const& data_in, unsigned int height);
    void                    drawMatrix(std::vector<std::vector<int> > const& data_in);

    void                    saveImage(std::string const& filename);

    void                    newImage();
    void                    newImage(unsigned int x_in, unsigned int y_in);

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
