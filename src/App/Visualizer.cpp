#include "App/Visualizer.hpp"

#include "ResourceHolder.hpp"
#include "ResourcePath.hpp"
#include "utilities.hpp"

#include "nlohmann/json.hpp"

#include <sstream>
#include <iostream>
#include <fstream>


Visualizer::Visualizer(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts):
    mTarget(outputTarget),
    mCanvas(800, 400, 2),
    size_x(800),
    size_y(400),
    mScrolling(false)
{
//    load(eng::getResourcePath() + "../build/results/1432427885_r2_k3_0.json");
//    mCanvas.maskFromImage(eng::getResourcePath() + "Textures/Plane.png", Canvas::Add);

    mCAHolder.push_back(CAHolder(3, 2, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(3, 1, 0, CA1d::Start::Random, CA1d::Type::Totalistic, 2, Canvas::BlendMode::Add));

    auto button_1 = std::make_shared<eng::Button>(fonts, textures);
    button_1->setPosition(1600.f, 100.f);
    button_1->setText("Scrolling");
    button_1->setToggle(true);
    button_1->setCallback(std::bind(&Visualizer::changeScrolling, this));
    mGUIContainer.pack(button_1);

    for(int i = 0; i < mCAHolder.size(); i++)
    {
        auto button = std::make_shared<eng::Button>(fonts, textures);
        button->setPosition(1600.f, 190.f + 90.f * i);
        button->setText("Change\nPalette " + std::to_string(i));
        button->setCallback(std::bind(&Visualizer::changePalettes, this, i));
        mGUIContainer.pack(button);
    }

    initializeCA();
    generate();
}

void Visualizer::update()
{
    if(mScrolling)
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
                updateRules();
                initializeCA();
                break;
            case sf::Keyboard::R:
                updateRules();
                break;
            case sf::Keyboard::M:
                break;
            case sf::Keyboard::S:
                save();
                break;
            case sf::Keyboard::C:
                changePalettes(0);
                break;
            default:
                break;
        }
    } else
    {
        mGUIContainer.handleEvent(event);
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

void Visualizer::changePalettes(int i)
{
    mCAHolder[i].palette = eng::modulo(++mCAHolder[i].palette, 5);
}

void Visualizer::save()
{
    std::stringstream ss;
    ss  << "results/" << rand() << "_r" << mCAHolder[0].radius << "_k" << mCAHolder[0].states << "_" << mCAHolder[0].palette;

    mCanvas.save(ss.str() + ".png");

    nlohmann::json data_out = nlohmann::json::array();

    std::ofstream datafile(ss.str() + ".json");
    if(datafile.is_open())
    {
        for(auto& i: mCAHolder)
            data_out.push_back(i);

        datafile << std::setw(4) << data_out << std::endl;
        datafile.close();
    }
}

void Visualizer::load(std::string filename)
{
    std::string line;
    nlohmann::json data_in;

    std::ifstream datafile(filename);
    if(datafile.is_open())
    {
        datafile >> data_in;
        datafile.close();
    }

    auto i = data_in[0].get<CAHolder>();
    auto j = data_in[1].get<CAHolder>();
    mCAHolder.push_back(std::move(i));
    mCAHolder.push_back(std::move(j));

    for(auto& i : mCAHolder)
        i.updateCA();
}
