//
//  State.hpp
//  camusic
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef state_hpp
#define state_hpp

#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.h"
#include "CA/CA1d.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
    typedef std::unique_ptr<State>          Ptr;

    struct Context
    {
        Context(sf::RenderWindow& window, CA1d* ca, FontHolder* fonts);

        sf::RenderWindow*                   window;
        CA1d*                               ca1d;
        FontHolder*                         fonts;
    };


public:
                                            State(StateStack& stack, Context* context);
    virtual                                 ~State();

    virtual void                            draw() = 0;
    virtual bool                            update() = 0;
    virtual bool                            handleEvent(const sf::Event& event) = 0;

protected:
    void                                    requestStackPush(States::ID stateID);

    void                                    requestStackPop();
    void                                    requestStateClear();

    Context*                                getContext() const;

protected:
    StateStack*                             mStack;
    Context*                                mContext;
};

#endif /* state_hpp */
