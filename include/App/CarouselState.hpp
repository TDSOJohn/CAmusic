//
//  CarouselState.hpp
//  camusic
//

#ifndef CarouselState_hpp
#define CarouselState_hpp

#include "App/Carousel.hpp"
#include "State.hpp"
#include "StateStack.hpp"
#include "App/Visualizer.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class CarouselState : public eng::State
{
public:
    CarouselState(eng::StateStack& stack, eng::State::Context context);

    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);

private:
    Carousel            mCarousel;
};

#endif /* CarouselState_hpp */
