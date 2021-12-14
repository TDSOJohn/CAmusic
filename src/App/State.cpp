//
//  State.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "App/State.hpp"
#include "App/StateStack.hpp"


State::Context::Context(sf::RenderWindow& window, CA1d* ca, FontHolder fonts):
    window(&window),
    ca1d(ca),
    fonts(&fonts)
{
}

State::State(StateStack& stack, Context context) :
    mStack(&stack),
    mContext(context)
{

}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStateClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}
