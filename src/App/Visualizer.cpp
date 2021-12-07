#include "App/Visualizer.hpp"

#include "utilities.hpp"

#include <sstream>


Visualizer::Visualizer(sf::RenderTarget& outputTarget):
    mTarget(outputTarget),
    mTexture(),
    mStates(3),
    mRadius(1),
    size_x(720),
    size_y(450),
    mStart(CA1d::Start::Middle),
    mType(CA1d::Type::Standard),
    mScaling(2),
    ca1d(NULL),
    buffer(720 * 450 * 4),
    mPalette(0),
    mtf_p(),
    mRule({})
{
    mTexture.create(size_x, size_y);
    mSprite.setScale(mScaling, mScaling);
}

void Visualizer::update()
{
}

void Visualizer::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::N:
                newCA();
                break;
            case sf::Keyboard::R:
                mStart = CA1d::Start::Random;
                generate();
                break;
            case sf::Keyboard::M:
                mStart = CA1d::Start::Middle;
                generate();
                break;
            case sf::Keyboard::S:
                save();
                break;
        }
    }
}

void Visualizer::newCA()
{
    mRule = {};
    mPalette = rand()%4;
    if(ca1d != NULL)
    {
        delete ca1d;
        ca1d = NULL;
    }

    ca1d = new CA1d(mType, mRadius, mStates, mRule);
    mRule = ca1d->getRule();

    generate();
}

void Visualizer::drawLine(std::vector<int> data_in, int y)
{
    std::vector<Pixel> palette = std::move(state_to_palette(mStates, mPalette));

    for(int i = 0; i < data_in.size(); i++)
    {
        int buffer_x_val = y * size_x * 4;
        Pixel rgb_val = palette[data_in[i]];
        buffer[buffer_x_val + i*4] = rgb_val.r;
        buffer[buffer_x_val + i*4+1] = rgb_val.g;
        buffer[buffer_x_val + i*4+2] = rgb_val.b;
        buffer[buffer_x_val + i*4+3] = rgb_val.a;
    }
}

void Visualizer::generate()
{
    ca1d->initialize(size_x, mStart);
    for(int i = 0; i < size_y; i++)
    {
        ca1d->generate();
        drawLine(ca1d->getData(), i);
    }
    uint8_t* buffer_tmp = buffer.data();
    mTexture.update(buffer_tmp);
}

//  NOT WORKING
void Visualizer::scrolling()
{
    int x = size_x * 4;
    buffer.erase(buffer.begin(), buffer.begin() + x);
    for(int i = 0; i < x; i++)
    {
        ca1d->generate();
        drawLine(ca1d->getData(), size_y - 1);
    }
    uint8_t* buffer_tmp = buffer.data();
    mTexture.update(buffer_tmp);
}

void Visualizer::draw()
{
    mSprite.setTexture(mTexture);
    mTarget.draw(mSprite);
}

void Visualizer::save()
{
    std::stringstream ss;
    ss << "results/" << baseNtoDecimal(mRule, mStates) << ".png";
    mTexture.copyToImage().saveToFile(ss.str());
}
