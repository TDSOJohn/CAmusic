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


SettingsState::SettingsState(StateStack& stack, Context context):
    State(stack, context),
    mSettings(context)
{
    std::cout << "SettingsState built!" << std::endl;
}

void SettingsState::draw()
{
    mSettings.draw();
}

bool SettingsState::update()
{
    mSettings.update();
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPop();

    mSettings.handleEvent(event);

    return true;
}
