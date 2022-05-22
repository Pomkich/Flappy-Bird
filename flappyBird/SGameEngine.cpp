#include "SGameEngine.h"

SGameEngine::SGameEngine() {
	window.create(sf::VideoMode(800, 600), "sue");
}

void SGameEngine::addObject(std::shared_ptr<GameObject> p_obj) {
    if (!game_objects.empty()) {
        for (auto& obj : game_objects) {
            if (obj->getName() == p_obj->getName()) {   // unique name check
                std::cout << "SGameEngine::addObject: found duplicate name, name of GameObject must be unique" << std::endl;
                return;
            }
        }
    }
    game_objects.push_back(p_obj);
}

void SGameEngine::deleteObject(std::string obj_name) {
    if (!game_objects.empty()) {
        game_objects.erase(std::remove_if(game_objects.begin(), game_objects.end(), [obj_name](std::shared_ptr<GameObject> obj) { return obj->getName() == obj_name; }), game_objects.end());
    }
}

void SGameEngine::HandleInput(sf::Event input) {
    if (!game_objects.empty()) {
        for (auto& object : game_objects) {
            object->HandleInput(input);
        }
    }
}

void SGameEngine::CheckCollision() {
    if (game_objects.size() > 1) {
        for (int checkable_obj = 0; checkable_obj < game_objects.size(); checkable_obj++) {
            for (int obj_oncheck = checkable_obj + 1; obj_oncheck < game_objects.size(); obj_oncheck++) {
                auto rect1 = game_objects[checkable_obj]->getBoundingRect();
                auto rect2 = game_objects[obj_oncheck]->getBoundingRect();
                if (std::abs(rect1.getPosition().x - rect2.getPosition().x) <= rect2.getSize().x &&
                    std::abs(rect1.getPosition().y - rect2.getPosition().y) <= rect2.getSize().y) {
                    game_objects[checkable_obj]->onCollide(game_objects[obj_oncheck]);
                    game_objects[obj_oncheck]->onCollide(game_objects[checkable_obj]);
                }
            }
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
    window.setKeyRepeatEnabled(false); // better disable for better perfomance
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
        CheckCollision();
        Update();
        Render();
    }
}