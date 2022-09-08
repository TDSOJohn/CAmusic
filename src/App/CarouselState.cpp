//
//  CarouselState.cpp
//  camusic
//

#include "App/CarouselState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


CarouselState::CarouselState(eng::StateStack& stack, eng::State::Context context):
    State(stack, context),
    mCarousel(*context.window, *context.textures, *context.fonts)
{
}

void CarouselState::draw()
{
    mCarousel.draw();
}

bool CarouselState::update(sf::Time dt)
{
    mCarousel.update();
    return true;
}

bool CarouselState::handleEvent(const sf::Event& event)
{
    // P pressed, trigger the settings screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
//        mContext->ca1d = mCarousel.getCA();
        requestStackPush(eng::States::Settings);
    }
    else
        mCarousel.handleEvent(event);

    return true;
}
