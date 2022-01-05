#include "utilities.hpp"
#include "App/Canvas.hpp"


Canvas::Canvas(unsigned int size_x, unsigned int size_y, unsigned int global_scaling):
    mSizeX(size_x),
    mSizeY(size_y),
    mGlobalScaling(global_scaling),
    mPalette(0)
{
    //  size_x multiplied by 4 because it stores r, g, b, a values
    mBuffer = new uint8_t[mSizeX * mSizeY * 4];
    clearBuffer();

    mTexture.create(mSizeX, mSizeY);
    mSprite.setScale(mGlobalScaling, mGlobalScaling);
}

void Canvas::drawLine(std::vector<int> data_in, int y, int states, BlendMode blend)
{
    std::vector<Pixel> palette = std::move(state_to_palette(states, mPalette));

    if(y == 0)
        mPalette = rand()%5;
    if(y >= mSizeY)
        std::cout << "ERROR: y is too big" << std::endl;

    for(int i = 0; i < data_in.size(); i++)
    {
        Pixel rgb_val = palette[data_in[i]];
        //  offset is every row before the y value
        int buffer_offset = y * mSizeX * 4;

        if(blend == BlendMode::Add)
        {
            mBuffer[buffer_offset + i*4] = std::max(std::min(mBuffer[buffer_offset + i*4] + rgb_val.r, 255), 0);
            mBuffer[buffer_offset + i*4+1] = std::max(std::min(mBuffer[buffer_offset + i*4+1] + rgb_val.g, 255), 0);
            mBuffer[buffer_offset + i*4+2] = std::max(std::min(mBuffer[buffer_offset + i*4+2] + rgb_val.b, 255), 0);
            mBuffer[buffer_offset + i*4+3] = 255;//std::max(std::min(mBuffer[buffer_offset + i*4+3] + rgb_val.a, 255), 0);
        }
        else if(blend == BlendMode::Subtract)
        {
            mBuffer[buffer_offset + i*4] = std::max(std::min(mBuffer[buffer_offset + i*4] - rgb_val.r, 255), 0);
            mBuffer[buffer_offset + i*4+1] = std::max(std::min(mBuffer[buffer_offset + i*4+1] - rgb_val.g, 255), 0);
            mBuffer[buffer_offset + i*4+2] = std::max(std::min(mBuffer[buffer_offset + i*4+2] - rgb_val.b, 255), 0);
            mBuffer[buffer_offset + i*4+3] = 255;//std::max(std::min(mBuffer[buffer_offset + i*4+3] - rgb_val.a, 255), 0);
        }
    }
}

void Canvas::clearBuffer()
{
    mPalette = rand()%5;
    for(int i = 0; i < (mSizeX * mSizeY * 4); i++)
        mBuffer[i] = 0;
}

//  -->IMPROVE<-- try to put it somewhere else
void Canvas::updateTexture()
{
    mTexture.update(mBuffer);
    mSprite.setTexture(mTexture);
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite);
}
