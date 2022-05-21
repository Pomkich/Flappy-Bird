#include "SGameEngine.h"

SGameEngine::SGameEngine() {
	window.create(sf::VideoMode(800, 600), "sue");
}

void SGameEngine::addObject(std::shared_ptr<GameObject> p_obj) {
    game_objects.push_back(p_obj);
}

void SGameEngine::HandleInput(sf::Event input) {
    if (!game_objects.empty()) {
        for (auto& object : game_objects) {
            object->HandleInput(input);
        }
    }
}

void SGameEngine::Update() {
    if (!game_objects.empty()) {
        for (auto& object : game_objects) {
            object->Update();
        }
    }
}

void SGameEngine::Render() {
    window.clear(sf::Color::Black);

    if (!game_objects.empty()) {
        for (auto& object : game_objects) {
            window.draw(object->getSprite());
        }
    }

    window.display();
}

void SGameEngine::Start() {
    window.setActive(true);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event input;
        while (window.pollEvent(input))
        {
            HandleInput(input);
            if (input.type == sf::Event::Closed) {
                window.close();
            }
        }
        Update();
        Render();
    }
}