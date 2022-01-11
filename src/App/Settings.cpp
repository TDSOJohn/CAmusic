#include "App/Settings.hpp"

#include "utilities.hpp"

#include <sstream>
#include <iostream>


Settings::Settings(State::Context* context):
    mTarget(*context->window)
{
    mTextFields.push_back(InputField(*context->fonts, InputField::Type::NumbersOnly, "Rule"));
    mTextFields.back().setDefaultText(context->ca1d->getStates());
    mTextFields.back().setPosition(200.f, 200.f);
}

void Settings::update()
{
}

void Settings::handleEvent(sf::Event event)
{
    mTextFields.back().handleEvent(event);

    if(event.type == sf::Event::KeyPressed)
    {
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
