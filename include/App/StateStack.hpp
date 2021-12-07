//
//  StateStack.hpp
//  noGravitar
//
//  Created by Giovanni Basso on 25/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef statestack_hpp
#define statestack_hpp

#include "App/State.hpp"
#include "App/StateIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


namespace sf
{
    class Event;
    class RenderWindow;
}

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear
    };

public:
    explicit                            StateStack(State::Context context);

    template<typename T>
    void                                registerState(States::ID stateID);

    void                                update();
    void                                draw();
    void                                handleEvent(const sf::Event& event);

    void                                pushState(States::ID stateID);
    void                                popState();
    void                                clearStates();

    bool                                isEmpty() const;

private:
    State::Ptr                          createState(States::ID stateID);
    void                                applyPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action, States::ID stateID = States::None);

        Action                          action;
        States::ID                      stateID;
    };


private:
    std::vector<State::Ptr>             mStack;
    std::vector<PendingChange>          mPendingList;

    State::Context                      mContext;
    std::map<States::ID, std::function<State::Ptr()>> mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] = [this] ()
    {
        return State::Ptr(new T(*this, mContext));
    };
}



#endif /* statestack_hpp */
