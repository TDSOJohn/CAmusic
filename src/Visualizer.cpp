#include "Visualizer.hpp"

#include "Data/DataAnalyzer.hpp"
#include "utilities.hpp"

#include <sstream>


const sf::Time Visualizer::TimePerFrame = sf::seconds(1.f/60.f);

Visualizer::Visualizer():
    mWindow(sf::VideoMode(1600, 1200),
        "caMusic"),
    mStates(2),
    mRadius(1),
    mStart(CA1d::Start::Middle),
    mType(CA1d::Type::Standard),
    mScaling(2),
    ca1d(NULL),
    mtf_p(),
    mRule({}),
    mTexture()
{
    srand(time(NULL));

    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(60.f);
    mTexture.create(size_x, size_y);
}

void Visualizer::run()
{
    newCA();
    ca1d->initialize(size_x, mStart);

    while(mWindow.isOpen())
    {
        genBMP = false;
        genMIDI = false;
        genPRINT = true;

        processInput();
        update();
        render();
    }
}

void Visualizer::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();

        if (event.type == sf::Event::KeyPressed)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::N:
                    newCA();
                    break;
                case sf::Keyboard::R:
                    mStart = CA1d::Start::Random;
                    newCA();
                    break;
                case sf::Keyboard::M:
                    mStart = CA1d::Start::Middle;
                    newCA();
                    break;
                case sf::Keyboard::S:
                    save();
                    break;
            }
        }
    }
}

void Visualizer::update()
{
}

void Visualizer::render()
{
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());

    mSprite.setTexture(mTexture);
    mWindow.draw(mSprite);

    mWindow.display();
}

void Visualizer::newCA()
{
    if(ca1d != NULL)
    {
        delete ca1d;
        ca1d = NULL;
    }

    ca1d = new CA1d(mType, mRadius, mStates, mRule);

    generate();
}

void Visualizer::drawLine(std::vector<int> data_in, int y)
{
    for(int i = 0; i < data_in.size(); i++)
    {
        int buffer_x_val = y * size_x * 4;
        int rgb_val = data_in[i] * 255;
        buffer[buffer_x_val + i*4] = buffer[buffer_x_val + i*4+1] = buffer[buffer_x_val + i*4+2] = rgb_val;
        buffer[buffer_x_val + i*4+3] = 255;
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
    mTexture.update(buffer);
}

void Visualizer::preferences()
{
}

void Visualizer::save()
{
    std::stringstream ss;
    ss << "results/" << rand()%38290182 << ".png";
    mTexture.copyToImage().saveToFile(ss.str());
}
