#include "App/Application.hpp"
#include "App/VisualizerState.hpp"
#include "App/SettingsState.hpp"

#include <iostream>


Application::Application():
    mWindow(sf::VideoMode(1600, 800),
        "camusic"),
    mFonts(),
    mStateStack(State::Context(mWindow, nullptr, &mFonts))
{
    srand(time(NULL));

    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(60.f);

    registerStates();
    mStateStack.pushState(States::Visualizer);

    //  BUG :   Reference from include/ folder works
    //          reference from Resources/ folder doesn't
    mFonts.load(Fonts::Mono, "../Resources/Fonts/IBMPlexMono-Regular.ttf");
}

Application::~Application()
{
}

void Application::run()
{
    while(mWindow.isOpen())
    {
        processInput();
        update();
        draw();
    }
}

void Application::registerStates()
{
    mStateStack.registerState<VisualizerState>(States::Visualizer);
//    mStateStack.registerState<GameState>(States::Loading);
//    mStateStack.registerState<PauseState>(States::Save);
    mStateStack.registerState<SettingsState>(States::Settings);
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

void Application::update()
{
    mStateStack.update();
}

void Application::draw()
{
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());
    mStateStack.draw();
    mWindow.display();
}
