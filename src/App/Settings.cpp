#include "App/Settings.hpp"

#include "utilities.hpp"

#include <sstream>
#include <iostream>


Settings::Settings(State::Context* context):
    mTarget(*context->window)
{
    mTextFields.push_back(InputField(*context->fonts, "Rule"));
    mTextFields.back().setDefaultText(context->ca1d->getStates());
//    mTextFields.back().setDefaultText(3);
    mTextFields.back().setPosition(200.f, 200.f);
}

void Settings::update()
{
}

void Settings::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::S:
                save();
                break;
        }
    }
}

void Settings::draw()
{
    for(auto& i : mTextFields)
        mTarget.draw(i);
}

void Settings::save()
{
}
