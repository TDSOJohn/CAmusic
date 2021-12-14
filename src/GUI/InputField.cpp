#include <SFML/Graphics/RectangleShape.hpp>

#include "GUI/InputField.hpp"

#include <iostream>


InputField::InputField(FontHolder& fonts)
{
    //  ->BUG<-
    //  Works when path is from include/ but not from Resources/

    inputString = "chao";

    inputText.setFont(fonts.get(Fonts::Mono));
/*    inputText.setCharacterSize(30);
    inputText.setString("ciao");
    inputText.setPosition(60, 100);
    inputText.setFillColor(sf::Color::White);*/
}

InputField::~InputField()
{

}

void InputField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    std::cout << "started drawing" << std::endl;
    target.draw(inputText, states);
    std::cout << "finished drawing" << std::endl;
}
