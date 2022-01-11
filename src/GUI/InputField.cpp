#include <SFML/Graphics/RectangleShape.hpp>

#include "ResourceHolder.hpp"
#include "GUI/InputField.hpp"

#include <iostream>
#include <sstream>


InputField::InputField(FontHolder& fonts, Type type, const std::string& text):
    mType(type)
{
    description.setFont(fonts.get(Fonts::Mono));
    description.setCharacterSize(18);
    description.setString(text);
    description.setFillColor(sf::Color::White);

    inputText.setFont(fonts.get(Fonts::Mono));
    inputText.setCharacterSize(18);
    inputText.setString("");
    inputText.setFillColor(sf::Color::White);

    inputRect.setSize(sf::Vector2f(140.f, 60.f));
    inputRect.setPosition(60, 100);
    inputRect.setFillColor(sf::Color::Black);
    inputRect.setOutlineColor(sf::Color::Green);
    inputRect.setOutlineThickness(5.f);
}

InputField::~InputField()
{
}

void InputField::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::TextEntered)
    {
        char input = static_cast<char>(event.text.unicode);
        if(mType == Type::NumbersOnly || mType == Type::Chars)
        {
            if(input >= 48 && input <= 57)
                inputText.setString(inputText.getString() + input);
        }
        if(mType == Type::LettersOnly || mType == Type::Chars)
        {
            if((input >= 65 && input <= 90) || (input >= 97 && input <= 122))
                inputText.setString(inputText.getString() + input);
        }
    }
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace)
    {
        std::string temp = inputText.getString();
        temp.pop_back();
        inputText.setString(temp);
    }
}

void InputField::setPosition(const sf::Vector2f& position)
{
    description.setPosition(position);
    inputText.setPosition(position.x + 10.f, position.y + 60.f);
    inputRect.setPosition(position.x, position.y + 60.f);
}

void InputField::setPosition(float px, float py)
{
    setPosition(sf::Vector2f(px, py));
}

void InputField::setDefaultText(const std::string& str)
{
    inputText.setString(str);
}

void InputField::setDefaultText(int n)
{
    std::stringstream ss;
    ss << n;
    inputText.setString(ss.str());
}

void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(description, states);
    target.draw(inputRect, states);
    target.draw(inputText, states);
}
