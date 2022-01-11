#ifndef inputfield_hpp
#define inputfield_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceIdentifiers.h"


class InputField : public sf::Drawable
{
public:
    enum Type
    {
        NumbersOnly,
        LettersOnly,
        Chars,
    };

public:
    InputField(FontHolder& fonts, Type type, const std::string& text = "Default Text");
    ~InputField();

    void handleEvent(sf::Event event);

    void setPosition(const sf::Vector2f& position);
    void setPosition(float px, float py);

    void setDefaultText(const std::string& str);
    void setDefaultText(int n);

private:
    std::string         inputString;
    sf::Text            description;
    sf::Text            inputText;
    sf::RectangleShape  inputRect;

    Type                mType;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif // inputfield_hpp
