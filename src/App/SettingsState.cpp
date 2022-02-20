//
//  SettingsState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "App/SettingsState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>


SettingsState::SettingsState(eng::StateStack& stack, eng::State::Context context):
    State(stack, context),
    mSettings(context)
{
}

void SettingsState::draw()
{
    mSettings.draw();
}

bool SettingsState::update(sf::Time dt)
{
    mSettings.update();
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPop();
    else
        mSettings.handleEvent(event);

    return true;
}
