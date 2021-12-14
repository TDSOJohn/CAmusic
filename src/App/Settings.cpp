#include "App/Settings.hpp"

#include "utilities.hpp"

#include <sstream>
#include <iostream>


Settings::Settings(State::Context context):
    mTarget(*context.window)
{
    mTextFields.push_back(InputField(*context.fonts));

    inputText.setFont(mFont);
    inputText.setCharacterSize(30);
    inputText.setString("ciao");
    inputText.setPosition(60, 100);
    inputText.setFillColor(sf::Color::White);
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
    mTarget.draw(inputText);
    for(auto& i : mTextFields)
        mTarget.draw(i);
}

void Settings::save()
{
}
