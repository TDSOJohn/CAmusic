#include "App/Visualizer.hpp"

#include "ResourceHolder.hpp"
#include "ResourcePath.hpp"
#include "utilities.hpp"

#include <sstream>
#include <iostream>
#include <fstream>


Visualizer::Visualizer(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts):
    mTarget(outputTarget),
    mCanvas(400, 200, 4),
    size_x(400),
    size_y(200)
{
    mCanvas.maskFromImage(eng::getResourcePath() + "Textures/Plane.png", Canvas::Add);

    mCAHolder.push_back(CAHolder(3, 2, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(3, 1, 0, CA1d::Start::Random, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Subtract));

    initializeCA();
    generate();

    mTextures.load(eng::Textures::Buttons, eng::getResourcePath() + "Textures/Buttons.png");
}

void Visualizer::update()
{
    scroll();
}

void Visualizer::draw()
{
    mTarget.draw(mCanvas);
}

void Visualizer::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::N:
                updateRules();
                initializeCA();
                break;
            case sf::Keyboard::R:
                updateRules();
                break;
            case sf::Keyboard::M:
                randomizePalettes();
                mCAHolder.front().start = CA1d::Start::Middle;
                for(auto& i: mCAHolder)
                    i.ca1d->initialize(size_x, i.start);
                break;
            case sf::Keyboard::S:
                save();
                break;
            case sf::Keyboard::C:
                randomizePalettes();
                break;
                //  -->IMPROVE<-- IS IT OK TO PUT DEFAULT HERE?
            default:
                break;
        }
    }
}

void Visualizer::initializeCA()
{
    for(auto& i: mCAHolder)
        i.ca1d->initialize(size_x, i.start);
}

void Visualizer::updateRules()
{
    for(auto& i: mCAHolder)
    {
        if(i.ca1d != NULL)
            i.ca1d->setRule({});
    }
}

void Visualizer::generate()
{
    randomizePalettes();
    mCanvas.clearBuffer();

    for(auto& i: mCAHolder)
    {
        for(int j = 0; j < size_y; j++)
        {
            mCanvas.drawLine(i.ca1d->getData(), j, i.states, i.blendMode, i.palette);
            i.ca1d->generate();
        }
    }
    mCanvas.updateTexture();
}

void Visualizer::scroll()
{
    mCanvas.scroll();
    for(auto& i: mCAHolder)
    {
        mCanvas.drawLine(i.ca1d->getData(), (size_y - 1), i.states, i.blendMode, i.palette);
        i.ca1d->generate();
    }
}

void Visualizer::randomizePalettes()
{
    for(auto& i: mCAHolder)
        i.palette = rand()%5;
}

void Visualizer::save()
{
    std::stringstream ss;
    ss  << "results/" << rand() << "_r" << mCAHolder[0].radius << "_k" << mCAHolder[0].states << "_" << mCAHolder[0].palette;

    mCanvas.save(ss.str() + ".png");

    std::ofstream datafile;
    datafile.open(ss.str() + ".txt");
    for(auto& i : mCAHolder)
        datafile << i.ca1d->getRuleString() << "_r" << i.radius << "_k" << i.states << std::endl;
    datafile.close();
}

void Visualizer::load(std::string filename)
{
    std::string line;

    std::ifstream datafile(filename);
    if(datafile.is_open())
    {
        while(getline(datafile, line))
        {
            std::cout << line << std::endl;
        }
        datafile.close();
    }

    std::cout << line << std::endl;
}
