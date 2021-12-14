//
//  StateStack.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "App/StateStack.hpp"

#include <cassert>

#include <iostream>


StateStack::StateStack(State::Context context) :
    mStack(),
    mPendingList(),
    mContext(context),
    mFactories()
{
}

void StateStack::update()
{
    if(mStack.size() != 0)
        mStack.back()->update();

    applyPendingChanges();
}

void StateStack::draw()
{
    // Draw all active states from bottom to top
//    for(State::Ptr& state : mStack)
//        state->draw();
    mStack.back()->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
    if(mStack.size() != 0)
        mStack.back()->handleEvent(event);

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for(PendingChange change : mPendingList)
    {
        switch(change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID):
    action(action),
    stateID(stateID)
{
}
