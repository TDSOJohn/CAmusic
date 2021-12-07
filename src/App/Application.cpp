#include "App/Application.hpp"
#include "App/VisualizerState.hpp"

#include <iostream>


Application::Application():
    mWindow(sf::VideoMode(1440, 720),
        "camusic"),
    mStateStack(State::Context(mWindow, nullptr))
{
    srand(time(NULL));

    mWindow.setKeyRepeatEnabled(false);
    mWindow.setFramerateLimit(30.f);

    registerStates();
    mStateStack.pushState(States::Visualizer);
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
//    mStateStack.registerState<SettingsState>(States::Settings);
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
}

void Application::draw()
{
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());
    mStateStack.draw();
    mWindow.display();
}
