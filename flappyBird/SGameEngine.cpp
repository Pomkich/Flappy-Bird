#include "SGameEngine.h"

SGameEngine::SGameEngine() {
	window.create(sf::VideoMode(800, 600), "sue");
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

    // drawing
    window.display();
}

void SGameEngine::Start() {
    window.setActive(true);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Update();
        Render();
    }
}