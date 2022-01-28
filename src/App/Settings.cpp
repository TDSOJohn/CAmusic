#include "App/Settings.hpp"

#include "utilities.hpp"

#include <sstream>
#include <iostream>


Settings::Settings(eng::State::Context context):
    mTarget(*context.window)
{
}

void Settings::update()
{
}

void Settings::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
    }
}

void Settings::draw()
{
}

void Settings::save()
{
}
