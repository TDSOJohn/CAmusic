#include "App/Visualizer.hpp"

#include "utilities.hpp"

#include <sstream>
#include <iostream>


Visualizer::Visualizer(sf::RenderTarget& outputTarget):
    mTarget(outputTarget),
    mCanvas(800, 400, 2),
    size_x(800),
    size_y(400)
{
    mCAHolder.push_back(CAHolder(3, 2, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(2, 1, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Subtract));

    newCA();
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
                mCAHolder.front().start = CA1d::Start::Random;
                generate();
                break;
            case sf::Keyboard::M:
                mCAHolder.front().start = CA1d::Start::Middle;
                generate();
                break;
            case sf::Keyboard::S:
                save();
                break;
                //  -->IMPROVE<-- IS IT OK TO PUT DEFAULT HERE?
            default:
                break;
        }
    }
}

void Visualizer::newCA()
{
    for(auto& i: mCAHolder)
    {
        if(i.ca1d != NULL)
            i.ca1d.reset();

        i.ca1d = std::make_unique<CA1d>(i.type, i.radius, i.states);
    }
    generate();
}

void Visualizer::generate()
{
    mCanvas.clearBuffer();

    for(auto& i: mCAHolder)
    {
        i.ca1d->initialize(size_x, i.start);
        for(int j = 0; j < size_y; j++)
        {
            mCanvas.drawLine(i.ca1d->getData(), j, i.states, i.blendMode);
            i.ca1d->generate();
        }
    }
    mCanvas.updateTexture();
}

//  -->BUG<-- NOT WORKING
void Visualizer::scrolling()
{
/*    int x = size_x * 4;
    buffer.erase(buffer.begin(), buffer.begin() + x);
    for(int i = 0; i < x; i++)
    {
        ca1d_1->generate();
        drawLine(ca1d_1->getData(), size_y - 1);
        ca1d_2->generate();
        drawLine(ca1d_2->getData(), size_y - 1);
    }
    uint8_t* buffer_tmp = buffer.data();
    mTexture.update(buffer_tmp);
    */
}

void Visualizer::draw()
{
    mTarget.draw(mCanvas);
}

void Visualizer::save()
{
    std::stringstream ss;
    ss << "results/" << baseNtoDecimal(mCAHolder[0].ca1d->getRule(), mCAHolder[0].states) << "_r" << mCAHolder[0].radius << "_k" << mCAHolder[0].states << "_" << mCAHolder[0].palette << ".png";
    mCanvas.save(ss.str());
}
