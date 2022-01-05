#ifndef canvas_hpp
#define canvas_hpp

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>

#include <iostream>
#include <string>


class Canvas: public sf::Drawable
{
public:
    enum BlendMode
    {
        Add,
        Subtract,
        Average
    };

public:
    Canvas(unsigned int size_x, unsigned int size_y, unsigned int global_scaling);

    void                                drawLine(std::vector<int> data_in, int y, int states, BlendMode blend);
    void                                updateTexture();

    void                                clearBuffer();
    void                                save(std::string filename);

private:
    sf::Texture                         mTexture;
    sf::Sprite                          mSprite;

    uint8_t                             *mBuffer;
    unsigned int                        mGlobalScaling;
    unsigned int                        mPalette;

    unsigned int                        mSizeX;
    unsigned int                        mSizeY;

private:
    virtual void                        draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //canvas_hpp
