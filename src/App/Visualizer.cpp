#include "App/Visualizer.hpp"

#include "utilities.hpp"

#include <sstream>
#include <iostream>


Visualizer::Visualizer(sf::RenderTarget& outputTarget):
    mTarget(outputTarget),
    mCanvas(800, 400, 2),
    mStates(3),
    mRadius(2),
    size_x(800),
    size_y(400),
    mStart(CA1d::Start::Middle),
    mType(CA1d::Type::Totalistic),
    mScaling(2),
    mPalette(0),
    mCa1dSize(2)
{
    for(int i = 0; i < mCa1dSize; i++)
        mCa1dArray[i] = nullptr;

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
                //  -->IMPROVE<-- IS IT OK TO PUT DEFAULT HERE?
            default:
                break;
        }
    }
}

void Visualizer::newCA()
{
    mPalette = rand()%5;
    for(int i = 0; i < mCa1dSize; i++)
    {
        if(mCa1dArray[i] != NULL)
        {
            delete mCa1dArray[i];
            mCa1dArray[i] = NULL;
        }
        mCa1dArray[i] = new CA1d(mType, mRadius, mStates, {});
    }
    generate();
}

void Visualizer::generate()
{
    mCanvas.clearBuffer();

    for(int i = 0; i < mCa1dSize; i++)
    {
        mCa1dArray[i]->initialize(size_x, mStart);
        for(int j = 0; j < size_y; j++)
        {
            mCa1dArray[i]->generate();
//                if(i == 0)
                    mCanvas.drawLine(mCa1dArray[i]->getData(), j, mStates, Canvas::BlendMode::Add);
//                else
//                    mCanvas.drawLine(mCa1dArray[i]->getData(), j, mStates, Canvas::BlendMode::Subtract);
        }
        mCa1dArray[i]->initialize(size_x, mStart);
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
/*    std::stringstream ss;
    ss << "results/" << baseNtoDecimal(mCa1dArray[0]->getRule(), mStates) << "_r" << mCa1dArray[0]->getRadius() << "_k" << mCa1dArray[0]->getStates() << "_" << mPalette << ".png";
    mTexture.copyToImage().saveToFile(ss.str());
    */
}
