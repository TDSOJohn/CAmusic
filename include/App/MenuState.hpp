#ifndef MenuState_hpp
#define MenuState_hpp

#include "State.hpp"
#include "GUI/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public eng::State
{
public:
    MenuState(eng::StateStack& stack, eng::State::Context context);

    virtual void                draw();
    virtual bool                update(sf::Time dt);
    virtual bool                handleEvent(const sf::Event& event);

private:
    eng::Container              mGUIContainer;
};

#endif /* MenuState_hpp */