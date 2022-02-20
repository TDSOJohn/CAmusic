#include "utilities.hpp"
#include "App/Canvas.hpp"


Canvas::Canvas(unsigned int size_x, unsigned int size_y, unsigned int global_scaling):
    mSizeX(size_x),
    mSizeY(size_y),
    mGlobalScaling(global_scaling),
    mPalette(0)
{
    //  Size multiplied by 4 because it stores r, g, b, a values
    mBuffer.resize(mSizeX * mSizeY * 4);
//    mMaskedBuffer.resize(mSizeX * mSizeY * 4);
    clearBuffer();

    mTexture.create(mSizeX, mSizeY);
    mSprite.setScale(mGlobalScaling, mGlobalScaling);
}

void Canvas::drawLine(std::vector<int> data_in, int y, int states, BlendMode blend, int palette_id)
{
    std::vector<eng::Pixel> palette = std::move(state_to_palette(states, palette_id));

    //  -->IMPROVE<-- not the best option, better have some updatePalette() function
    if(y >= mSizeY)
        std::cout << "ERROR: y is too big" << std::endl;

    for(int i = 0; i < data_in.size(); i++)
    {
        eng::Pixel rgb_val = palette[data_in[i]];
        //  offset is every row before the y value
        int buffer_offset = y * mSizeX * 4;

        if(blend == BlendMode::Add)
        {
            mBuffer[buffer_offset + i*4] = std::max(std::min(mBuffer[buffer_offset + i*4] + rgb_val.r, 255), 0);
            mBuffer[buffer_offset + i*4+1] = std::max(std::min(mBuffer[buffer_offset + i*4+1] + rgb_val.g, 255), 0);
            mBuffer[buffer_offset + i*4+2] = std::max(std::min(mBuffer[buffer_offset + i*4+2] + rgb_val.b, 255), 0);
            mBuffer[buffer_offset + i*4+3] = 255;
        }
        else if(blend == BlendMode::Subtract)
        {
            mBuffer[buffer_offset + i*4] = std::max(std::min(mBuffer[buffer_offset + i*4] - rgb_val.r, 255), 0);
            mBuffer[buffer_offset + i*4+1] = std::max(std::min(mBuffer[buffer_offset + i*4+1] - rgb_val.g, 255), 0);
            mBuffer[buffer_offset + i*4+2] = std::max(std::min(mBuffer[buffer_offset + i*4+2] - rgb_val.b, 255), 0);
            mBuffer[buffer_offset + i*4+3] = 255;
        }
        else if(blend == BlendMode::Overwrite)
        {
            mBuffer[buffer_offset + i*4] = std::max(std::min(static_cast<int>(rgb_val.r), 255), 0);
            mBuffer[buffer_offset + i*4+1] = std::max(std::min(static_cast<int>(rgb_val.g), 255), 0);
            mBuffer[buffer_offset + i*4+2] = std::max(std::min(static_cast<int>(rgb_val.b), 255), 0);
            mBuffer[buffer_offset + i*4+3] = 255;
        }
    }
    updateTexture();
}

void Canvas::maskFromImage(std::string path_in, BlendMode blend)
{
    if(!mMaskingImage.loadFromFile(path_in))
        std::cout << "Error loading the image!" << std::endl;

    std::cout << mMaskingImage.getPixel(1,1).a << std::endl;
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
}

void Canvas::applyMask()
{
    std::copy(mBuffer.begin(), mBuffer.end(), mMaskedBuffer.begin());
    sf::Vector2u imageSize = mMaskingImage.getSize();

    for(int i = 0; i < imageSize.y; i++)
    {
        //  Offsetting to the correct row of pixels in mBuffer
        int buffer_offset = i * mSizeX * 4;
        for(int j = 0; j < imageSize.x; j++)
        {
            if(mMaskingImage.getPixel(j, i).a == 0)
                mMaskedBuffer[buffer_offset + j*4] = mMaskedBuffer[buffer_offset + j*4 + 1] = mMaskedBuffer[buffer_offset + j*4 + 2] = 0;
        }
    }
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

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite);
}
