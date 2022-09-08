#ifndef canvas_hpp
#define canvas_hpp


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

#include "Utility.hpp"

#include <iostream>
#include <string>


class Canvas: public sf::Drawable
{
public:
    enum BlendMode
    {
        Add,
        Subtract,
        Average,
        Overwrite
    };

public:
    Canvas(unsigned int size_x, unsigned int size_y, unsigned int global_scaling);

    void                                drawLine(std::vector<int> data_in, int y, int states, int scaling, BlendMode blend, eng::Pixel target);
    void                                drawImage(std::vector<std::vector<int> > data_in, int states, int scaling, BlendMode blend, eng::Pixel rgb);

    void                                updateTexture();

    void                                scroll();
    void                                clearBuffer();

    void                                save(std::string filename);

private:
    sf::Image                           mMaskingImage;
    sf::Texture                         mTexture;
    sf::Sprite                          mSprite;

    std::vector<uint8_t>                mBuffer;
    std::vector<uint8_t>                mMaskedBuffer;
    unsigned int                        mGlobalScaling;
    unsigned int                        mPalette;

    unsigned int                        mSizeX;
    unsigned int                        mSizeY;

private:
    void                                drawPixel(int x, int y, int scaling, BlendMode blend, eng::Pixel pixel_in);

    virtual void                        draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //canvas_hpp
