#include "App/Carousel.hpp"

#include "ResourceHolder.hpp"
#include "ResourcePath.hpp"
#include "utilities.hpp"
#include "App/CAHolder.hpp"

#include "json/single_include/nlohmann/json.hpp"

#include <sstream>
#include <iostream>
#include <fstream>


const int globalScaling = 2;


Carousel::Carousel(sf::RenderTarget& outputTarget, const eng::TextureHolder& textures, const eng::FontHolder& fonts):
    mTarget(outputTarget),
    mTextures(textures),
    mFonts(fonts),
    mCanvas(outputTarget.getSize().x / globalScaling, outputTarget.getSize().y / globalScaling, globalScaling),
    size_x(outputTarget.getSize().x / globalScaling),
    size_y(outputTarget.getSize().y / globalScaling),
    global_scaling(globalScaling),
    updateCounter(0),
    frameCounter(0),
    directionCounter(0),
    mScrolling(true)
{
    std::cout << "x: " << outputTarget.getSize().x << " y: " << outputTarget.getSize().y << std::endl;
    mCAHolder.push_back(CAHolder(3, 1, {255, 255, 255}, CA1d::Start::Random, CA1d::Type::Standard, size_x, 1, Canvas::BlendMode::Add));
    mCAHolder.push_back(CAHolder(2, 2, {255, 0, 255}, CA1d::Start::Random, CA1d::Type::Totalistic, size_x, 1, Canvas::BlendMode::Subtract));
    mCAHolder.push_back(CAHolder(3, 2, {255, 255, 0}, CA1d::Start::Left, CA1d::Type::Totalistic, size_x, 1, Canvas::BlendMode::Add));

    buildGUI();

    initializeCA();
    generate();
}

void Carousel::update()
{
    frameCounter++;

    //  Update rule
    if(frameCounter >= 120)
    {
        changeRule(updateCounter);
        frameCounter = 0;
        updateCounter = eng::modulo(++updateCounter, mCAHolder.size());
        directionCounter = !directionCounter;
    }
    //  Update colors palette
    if(frameCounter%4 == 0)
        changePalettes(updateCounter);

    for(int i = 0; i < mCAHolder.size(); i++)
    {
        if(mCAHolder[i].ca1d->isStatic())
            initializeCA(i);
    }
    
    if(mScrolling)
        scroll();
}

void Carousel::draw()
{
    mTarget.draw(mCanvas);
    mTarget.draw(mGUIContainer);
}

void Carousel::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S)
        save();
    mGUIContainer.handleEvent(event);
}

void Carousel::initializeCA(int i)
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

void Carousel::changeRule(int i)
{
    if(mCAHolder[i].ca1d != NULL)
        mCAHolder[i].ca1d->setRule({});
}

void Carousel::generate()
{
    mCanvas.clearBuffer();

    for(auto& i: mCAHolder)
    {
        for(int y = 0; y < size_y; y += i.scaling)
        {
            mCanvas.drawLine(i.ca1d->getData(), y, i.states, i.scaling, i.blendMode, i.rgb);
            i.ca1d->generate();
        }
    }
    mCanvas.updateTexture();
}

void Carousel::resetAndGenerate()
{
    initializeCA();
    generate();
}

//  -->BUG<-- SCROLL DOESN'T WORK PROPERLY FOR MIXED CA SCALINGS
void Carousel::scroll()
{
    mCanvas.scroll();
    for(auto& i: mCAHolder)
    {
        mCanvas.drawLine(i.ca1d->getData(), (size_y - i.scaling), i.states, i.scaling, i.blendMode, i.rgb);
        i.ca1d->generate();
    }
}

void Carousel::changePalettes(int i)
{
    if(directionCounter == 0)
    {
        mCAHolder[i].rgb = {static_cast<uint8_t>(eng::modulo(mCAHolder[i].rgb.r + 2, 256)),
                            static_cast<uint8_t>(eng::modulo(mCAHolder[i].rgb.g - 3, 256)),
                            static_cast<uint8_t>(eng::modulo(mCAHolder[i].rgb.b - 2, 256))};        
    }
    if (directionCounter == 1)
        mCAHolder[i].rgb = {static_cast<uint8_t>(eng::modulo(mCAHolder[i].rgb.r - 3, 256)),
                            static_cast<uint8_t>(eng::modulo(mCAHolder[i].rgb.g + 2, 256)),
                            static_cast<uint8_t>(eng::modulo(mCAHolder[i].rgb.b + 3, 256))};
}

void Carousel::changeStart(int i)
{
    if( i == -1)
    {
        for(auto& i : mCAHolder)
        {
            i.start = rotateStart(i.start);
        }
    }
    else
        mCAHolder[i].start = rotateStart(mCAHolder[i].start);
}

void Carousel::save()
{
    std::stringstream ss;
    ss  << "results/" << rand() << "_r" << mCAHolder[0].radius << "_k" << mCAHolder[0].states;

    mCanvas.save(ss.str() + ".png");
/*
    nlohmann::json data_out = nlohmann::json::array();

    std::ofstream datafile(ss.str() + ".json");
    if(datafile.is_open())
    {
        for(auto& i: mCAHolder)
            data_out.push_back(i);

        datafile << std::setw(4) << data_out << std::endl;
        datafile.close();
    }
    */
}

void Carousel::load(std::string filename)
{
}

void Carousel::buildGUI()
{
    int x = size_x * global_scaling;
    int y = size_y * global_scaling;

    auto save_btn = std::make_shared<eng::Button>(mFonts, mTextures);
    save_btn->setPosition(x, y - 150.f);
    save_btn->setText("Save");
    save_btn->setCallback(std::bind(&Carousel::save, this));
    mGUIContainer.pack(save_btn);
}
