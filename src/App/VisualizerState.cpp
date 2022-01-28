//
//  GameState.cpp
//  noGravitar
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#include "App/VisualizerState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>


VisualizerState::VisualizerState(eng::StateStack& stack, eng::State::Context context):
    State(stack, context),
    mVisualizer(*context.window, *context.fonts)
{
}

void VisualizerState::draw()
{
    mVisualizer.draw();
}

bool VisualizerState::update(sf::Time dt)
{
    mVisualizer.update();
    return true;
}

bool VisualizerState::handleEvent(const sf::Event& event)
{
    // P pressed, trigger the settings screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
//        mContext->ca1d = mVisualizer.getCA();
        requestStackPush(eng::States::Settings);
    }
    else
        mVisualizer.handleEvent(event);

    return true;
}
