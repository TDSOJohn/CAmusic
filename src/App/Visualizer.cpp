#include "App/Visualizer.hpp"

#include "ResourceHolder.hpp"
#include "ResourcePath.hpp"
#include "utilities.hpp"

#include <sstream>
#include <iostream>
#include <fstream>


Visualizer::Visualizer(sf::RenderTarget& outputTarget, const FontHolder& fonts):
    mTarget(outputTarget),
    mCanvas(800, 400, 2),
    size_x(800),
    size_y(400)
{
    mCAHolder.push_back(CAHolder(2, 1, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(3, 2, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Subtract));
    mCAHolder.push_back(CAHolder(2, 2, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(3, 1, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Subtract));

    newCA();
    generate();

    mTextures.load(Textures::Buttons, getResourcePath() + "Textures/Buttons.png");

    auto randomButton = std::make_shared<GUI::Button>(fonts, mTextures);
    randomButton->setPosition(1600, 0);
    randomButton->setText("Random\nPalette");
    randomButton->setCallback(std::bind(&Visualizer::randomizePalettes, this));

    mGUIContainer.pack(randomButton);
}

void Visualizer::update()
{
    scroll();
}

void Visualizer::draw()
{
    mTarget.draw(mCanvas);
    mTarget.draw(mGUIContainer);
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
/*                randomizePalettes();
                mCAHolder.front().start = CA1d::Start::Random;
                for(auto& i: mCAHolder)
                    i.ca1d->initialize(size_x, i.start);
*/

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
    for(auto& i: mCAHolder)
        i.ca1d->initialize(size_x, i.start);
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
