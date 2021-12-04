#ifndef bmpgenerator_hpp
#define bmpgenerator_hpp


#include <vector>

#include "../../bitmap/bitmap_image.hpp"



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

                            /// Default: 100x100px image, scaling = 1
                            BMPgenerator(int x_in = 100, int y_in = 100, int scale_in = 1);

                            /// draw an array of data horizontally at input height
    void                    drawData(std::vector<int> const& data_in, int height, int states_in);
    void                    drawMatrix(std::vector<std::vector<int> > const& data_in, int states_in);

    void                    saveFile(std::string const& filename);

    /// Create new bitmap image using size_x and size_y stored values
    void                    newFile();
    /// Create new bitmap image, pass x, y size and scaling as parameters
    /// If scaling is omitted, previous value is used
    void                    newFile(int x_in, int y_in, int scaling = 0);

    unsigned int            getScaling() const { return mScaling; }
    void                    setScaling(const int scaling_in) { mScaling = scaling_in; }

    int                     getPalette() const { return choosen; }
    void                    setPalette(const int palette_in) { choosen = palette_in; }

private:
    int                     size_x, size_y;
    int                     mScaling;
    bitmap_image*           mBMP;

    std::vector<palette>    mPalettes;
    int                     choosen;

private:
    void                    generatePalettes();
    void                    drawLine(std::vector<Pixel> const& data_in, int height);
};


#endif //bmpgenerator_hpp
