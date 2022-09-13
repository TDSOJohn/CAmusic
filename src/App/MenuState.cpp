#include "App/MenuState.hpp"

#include "ResourceHolder.hpp"
#include "GUI/Button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>



MenuState::MenuState(eng::StateStack& stack, eng::State::Context context):
    State(stack, context),
    mGUIContainer()
{
    auto carouselButton = std::make_shared<eng::Button>(*context.fonts, *context.textures);
    carouselButton->setPosition(300, 450);
    carouselButton->setText("Play");
    carouselButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(eng::States::Settings);
    });

    auto visualizerButton = std::make_shared<eng::Button>(*context.fonts, *context.textures);
    visualizerButton->setPosition(300, 550);
    visualizerButton->setText("Visualizer");
    visualizerButton->setCallback([this] ()
    {
        requestStackPush(eng::States::Game);
    });

    auto exitButton = std::make_shared<eng::Button>(*context.fonts, *context.textures);
    exitButton->setPosition(300, 650);
    exitButton->setText("Exit");
    exitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(carouselButton);
    mGUIContainer.pack(visualizerButton);
    mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}