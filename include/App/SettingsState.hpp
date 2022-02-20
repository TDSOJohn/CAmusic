//
//  SettingsState.hpp
//  camusic
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef SettingsState_hpp
#define SettingsState_hpp

#include "State.hpp"
#include "StateStack.hpp"
#include "App/Settings.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class SettingsState : public eng::State
{
public:
    SettingsState(eng::StateStack& stack, eng::State::Context context);

    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);

private:
    Settings            mSettings;
};

#endif /* SettingsState_hpp */
