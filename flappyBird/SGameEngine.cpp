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
        game_objects.erase(std::remove_if(game_objects.begin(), game_objects.end(), 
            [obj_name](std::shared_ptr<GameObject> obj) { return obj->getName() == obj_name; }),
            game_objects.end()
        );
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
                auto rect1 = game_objects[checkable_obj]->getBoundingRect();    // getting rectangles bounds
                auto rect2 = game_objects[obj_oncheck]->getBoundingRect();
                // simple collision detection of 2 rectangles
                if (std::abs(rect1.getPosition().x - rect2.getPosition().x) <= rect2.getSize().x &&
                    std::abs(rect1.getPosition().y - rect2.getPosition().y) <= rect2.getSize().y) {

                    auto center_rect1 = rect1.getPosition();
                    auto center_rect2 = rect2.getPosition();

                    center_rect1.x = center_rect1.x + (rect1.getSize().x / 2); 
                    center_rect1.y = center_rect1.y + (rect1.getSize().y / 2);
                    center_rect2.x = center_rect2.x + (rect2.getSize().x / 2);
                    center_rect2.y = center_rect2.y + (rect2.getSize().y / 2);

                    Side side1 = Side::left, side2 = Side::right;
                    if (center_rect1.x > center_rect2.x) {
                        side1 = Side::left; side2 = Side::right;
                    }
                    else {
                        side1 = Side::right; side2 = Side::left;
                    }
                    game_objects[checkable_obj]->onCollide(game_objects[obj_oncheck], side1);
                    game_objects[obj_oncheck]->onCollide(game_objects[checkable_obj], side2);

                    if (center_rect1.y > center_rect2.y) {
                        side1 = Side::up; side2 = Side::down;
                    }
                    else {
                        side1 = Side::down; side2 = Side::up;
                    }

                    game_objects[checkable_obj]->onCollide(game_objects[obj_oncheck], side1);
                    game_objects[obj_oncheck]->onCollide(game_objects[checkable_obj], side2);
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

    sf::Time elapsed;
    sf::Time lag = sf::milliseconds(0);

    while (window.isOpen())
    {
        elapsed = clock.restart();
        lag += elapsed;
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
        while (lag.asMilliseconds() > 32) {
            Update();
            std::cout << lag.asMilliseconds() << std::endl;
            lag -= sf::milliseconds(32);
        }
        Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // 16 milliseconds ~= 60 fps
    }
}