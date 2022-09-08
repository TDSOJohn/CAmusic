
#include "App/Application.hpp"
#include "App/CarouselState.hpp"
#include "App/VisualizerState.hpp"
#include "App/SettingsState.hpp"
#include "ResourcePath.hpp"

#include "State.hpp"

#include <iostream>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application():
    mWindow(sf::VideoMode(1920, 1080), "camusic"),
    mFonts(),
    mContext(mWindow, mTextures, mFonts),
    mStateStack(eng::State::Context(mWindow, mTextures, mFonts))
{
    srand(time(NULL));

    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(60.f);

    //  BUG :   Reference from include/ folder works
    //          reference from Resources/ folder doesn't
    mFonts.load(eng::Fonts::Mono, eng::getResourcePath() + "Fonts/IBMPlexMono-Regular.ttf");
    mTextures.load(eng::Textures::Buttons, eng::getResourcePath() + "Textures/Button.png");
    registerStates();
    mStateStack.pushState(eng::States::Menu);
}

Application::~Application()
{
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        processInput();
        update(TimePerFrame);

        if(mStateStack.isEmpty())
            mWindow.close();
        draw();
    }
}

void Application::registerStates()
{
    mStateStack.registerState<CarouselState>(eng::States::Menu);
    mStateStack.registerState<VisualizerState>(eng::States::Game);
    mStateStack.registerState<SettingsState>(eng::States::Settings);
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if(event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::draw()
{
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());
    mStateStack.draw();
    mWindow.display();
}
