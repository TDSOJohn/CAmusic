//
//  VisualizerState.hpp
//  camusic
//
//  Created by Giovanni Basso on 26/01/2021.
//  Copyright © 2021 Giovanni Basso. All rights reserved.
//

#ifndef VisualizerState_hpp
#define VisualizerState_hpp

#include "State.hpp"
#include "StateStack.hpp"
#include "App/Visualizer.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class VisualizerState : public eng::State
{
public:
    VisualizerState(eng::StateStack& stack, eng::State::Context context);

    virtual void        draw();
    virtual bool        update(sf::Time dt);
    virtual bool        handleEvent(const sf::Event& event);

private:
    Visualizer          mVisualizer;
};

#endif /* VisualizerState_hpp */
