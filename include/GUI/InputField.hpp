#ifndef inputfield_hpp
#define inputfield_hpp

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.h"

class InputField : public sf::Drawable
{
public:
    InputField(FontHolder fonts);
    ~InputField();

private:
    //  ->PROBLEM<-
    //  mFont is allocated and loaded with every InputField instance
    sf::Font            mFont;
    sf::String          inputString;
    sf::Text            inputText;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif // inputfield_hpp
