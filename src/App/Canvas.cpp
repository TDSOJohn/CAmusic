#include "utilities.hpp"
#include "App/Canvas.hpp"

#include <iostream>


Canvas::Canvas(unsigned int size_x, unsigned int size_y, unsigned int global_scaling):
    mSizeX(size_x),
    mSizeY(size_y),
    mGlobalScaling(global_scaling),
    mPalette(0)
{
    //  Size multiplied by 4 because it stores r, g, b, a values
    mBuffer.resize(mSizeX * mSizeY * 4);
    clearBuffer();

    mTexture.create(mSizeX, mSizeY);
    mSprite.setScale(mGlobalScaling, mGlobalScaling);
}

void Canvas::drawLine(std::vector<int> data_in, int y, int states, int scaling, BlendMode blend, int palette_id)
{
    std::vector<eng::Pixel> palette = std::move(state_to_palette(states, palette_id));

    if((y < 0) || (y >= mSizeY))
        std::cout << "ERROR: y is out of bounds" << std::endl;

    for(int x = 0; x < data_in.size(); x++)
    {
        eng::Pixel rgb_val = palette[data_in[x]];
        drawPixel(x, y, scaling, blend, rgb_val);
    }
}

void Canvas::drawImage(std::vector<std::vector<int> > data_in, int states, int scaling, BlendMode blend, int palette_id)
{
    for(int i = 0; i < data_in.size(); i++)
        drawLine(data_in[i], i, states, scaling, blend, palette_id);
}

//  -->IMPROVE<-- try to put it somewhere else
void Canvas::updateTexture()
{
//    applyMask();
//    uint8_t* buffer_tmp = mMaskedBuffer.data();
    uint8_t* buffer_tmp = mBuffer.data();
    mTexture.update(buffer_tmp);
    mSprite.setTexture(mTexture);
}

void Canvas::scroll()
{
    int x = mSizeX * 4;

    mBuffer.erase(mBuffer.begin(), mBuffer.begin() + x);
    mBuffer.resize(mSizeX * mSizeY * 4);

    uint8_t* buffer_tmp = mBuffer.data();
    mTexture.update(buffer_tmp);
    updateTexture();
}

void Canvas::clearBuffer()
{
    for(int i = 0; i < (mSizeX * mSizeY * 4); i++)
        mBuffer[i] = 0;
//        mBuffer[i] = mMaskedBuffer[i] = 0;
}

void Canvas::save(std::string filename)
{
    mTexture.copyToImage().saveToFile(filename);
}

void Canvas::drawPixel(int x, int y, int scaling, BlendMode blend, eng::Pixel pixel_in)
{
    if(y > mSizeY)
        std::cout << "Error: Y too big!" << std::endl;

    for(int y_s = 0; y_s < scaling; y_s++)
    {
        int buffer_offset = (y + y_s) * mSizeX * 4;
        for(int x_s = 0; x_s < scaling; x_s++)
        {
            if(blend == BlendMode::Add)
            {
                mBuffer[buffer_offset + (x*4*scaling) + (x_s*4)] = std::max(std::min(mBuffer[buffer_offset + (x*4*scaling) + (x_s*4)] + pixel_in.r, 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+1) + (x_s*4)] = std::max(std::min(mBuffer[buffer_offset + (x*4*scaling+1) + (x_s*4)] + pixel_in.g, 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+2) + (x_s*4)] = std::max(std::min(mBuffer[buffer_offset + (x*4*scaling+2) + (x_s*4)] + pixel_in.b, 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+3) + (x_s*4)] = 255;
            }
            else if(blend == BlendMode::Subtract)
            {
                mBuffer[buffer_offset + (x*4*scaling) + (x_s*4)] = std::max(std::min(mBuffer[buffer_offset + (x*4*scaling) + (x_s*4)] - pixel_in.r, 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+1) + (x_s*4)] = std::max(std::min(mBuffer[buffer_offset + (x*4*scaling+1) + (x_s*4)] - pixel_in.g, 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+2) + (x_s*4)] = std::max(std::min(mBuffer[buffer_offset + (x*4*scaling+2) + (x_s*4)] - pixel_in.b, 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+3) + (x_s*4)] = 255;
            }
            else if(blend == BlendMode::Overwrite)
            {
                mBuffer[buffer_offset + (x*4*scaling) + (x_s*4)] = std::max(std::min(static_cast<int>(pixel_in.r), 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+1) + (x_s*4)] = std::max(std::min(static_cast<int>(pixel_in.g), 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+2) + (x_s*4)] = std::max(std::min(static_cast<int>(pixel_in.b), 255), 0);
                mBuffer[buffer_offset + (x*4*scaling+3) + (x_s*4)] = 255;
            }
        }
    }
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite);
}
