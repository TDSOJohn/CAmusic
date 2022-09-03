#include "App/Visualizer.hpp"

#include "ResourceHolder.hpp"
#include "ResourcePath.hpp"
#include "utilities.hpp"

#include "json/single_include/nlohmann/json.hpp"

#include <sstream>
#include <iostream>
#include <fstream>


const int globalScaling = 8;


Visualizer::Visualizer(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts):
    mTarget(outputTarget),
    mTextures(textures),
    mFonts(fonts),
    mCanvas((outputTarget.getSize().x - 360)/globalScaling, outputTarget.getSize().y / globalScaling, 8),
    size_x((outputTarget.getSize().x - 360)/globalScaling),
    size_y(outputTarget.getSize().y / globalScaling),
    global_scaling(globalScaling),
    mScrolling(false)
{
    std::cout << "x: " << outputTarget.getSize().x << " y: " << outputTarget.getSize().y << std::endl;
    mCAHolder.push_back(CAHolder(3, 1, 0, CA1d::Start::Random, CA1d::Type::Standard, size_x, 1, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(2, 2, 0, CA1d::Start::Middle, CA1d::Type::Totalistic, size_x, 1, Canvas::BlendMode::Subtract));

    buildGUI();

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
    if(event.type == sf::Event::KeyReleased)
        generate();
    mGUIContainer.handleEvent(event);
}

void Visualizer::initializeCA(int i)
{
    if(i == -1)
    {
        for(auto& i: mCAHolder)
            i.ca1d->initialize(i.size, i.start);
    } else
    {
        if(mCAHolder[i].ca1d != NULL)
            mCAHolder[i].ca1d->initialize(mCAHolder[i].size, mCAHolder[i].start);
    }
}

void Visualizer::changeRule(int i)
{
    if(mCAHolder[i].ca1d != NULL)
        mCAHolder[i].ca1d->setRule({});
}

void Visualizer::generate()
{
    mCanvas.clearBuffer();

    for(auto& i: mCAHolder)
    {
        for(int y = 0; y < size_y; y += i.scaling)
        {
            mCanvas.drawLine(i.ca1d->getData(), y, i.states, i.scaling, i.blendMode, i.palette);
            i.ca1d->generate();
        }
    }
    mCanvas.updateTexture();
}

//  -->BUG<-- SCROLL DOESN'T WORK PROPERLY FOR DIFFERENT CA SCALINGS TOGHETHER
void Visualizer::scroll()
{
    mCanvas.scroll();
    for(auto& i: mCAHolder)
    {
        mCanvas.drawLine(i.ca1d->getData(), (size_y - i.scaling), i.states, i.scaling, i.blendMode, i.palette);
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

void Visualizer::buildGUI()
{
    int x = size_x * global_scaling;
    int y = size_y * global_scaling;

    auto button_1 = std::make_shared<eng::Button>(mFonts, mTextures);
    button_1->setPosition(x, 10.f);
    button_1->setText("Scrolling");
    button_1->setTogglable(true);
    button_1->setCallback(std::bind(&Visualizer::changeScrolling, this));
    mGUIContainer.pack(button_1);

    for(int i = 0; i < mCAHolder.size(); i++)
    {
        //  rule change button
        auto button1 = std::make_shared<eng::Button>(mFonts, mTextures);
        button1->setPosition(x, 100.f + 170.f * i);
        button1->setText("Change\nRule " + std::to_string(i));
        button1->setCallback(std::bind(&Visualizer::changeRule, this, i));
        mGUIContainer.pack(button1);

        //  CA Restart button
        auto button3 = std::make_shared<eng::Button>(mFonts, mTextures);
        button3->setPosition(x, 180.f + 170.f * i);
        button3->setText("Restart\nCA " + std::to_string(i));
        button3->setCallback(std::bind(&Visualizer::initializeCA, this, i));
        mGUIContainer.pack(button3);

        //  color change button
        auto button2 = std::make_shared<eng::Button>(mFonts, mTextures);
        button2->setPosition(x + 150.f, 100.f + 170.f * i);
        button2->setText("Change\nPalette " + std::to_string(i));
        button2->setCallback(std::bind(&Visualizer::changePalettes, this, i));
        mGUIContainer.pack(button2);
    }

    auto save_btn = std::make_shared<eng::Button>(mFonts, mTextures);
    save_btn->setPosition(x, y - 150.f);
    save_btn->setText("Save");
    save_btn->setTogglable(true);
    save_btn->setCallback(std::bind(&Visualizer::save, this));
    mGUIContainer.pack(save_btn);
}
