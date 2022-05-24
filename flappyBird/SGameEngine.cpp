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

// cannot be deleted right now, deletion will occur at the end of the game cycle
void SGameEngine::deleteObject(std::string obj_name) {
    if (!game_objects.empty()) {
        delete_list.push_back(obj_name);
    }
}

void SGameEngine::HandleInput(sf::Event input) {
    if (!game_objects.empty()) {
        for (auto& object : game_objects) {
            object->HandleInput(input);
        }
    }
}

//the function considers whether the smaller segment touches the larger one
bool largerIntersects(double x11, double x12, double x21, double x22) {
    if ((x11 >= x21 && x11 <= x22) || (x12 >= x21 && x12 <= x22)) {
        return true;
    }
    return false;
}

void SGameEngine::CheckCollision() {
    if (game_objects.size() > 1) {
        for (int checkable_obj = 0; checkable_obj < game_objects.size(); checkable_obj++) {
            for (int obj_oncheck = checkable_obj + 1; obj_oncheck < game_objects.size(); obj_oncheck++) {
                auto rect1 = game_objects[checkable_obj]->getBoundingRect();    // getting rectangles bounds
                auto rect2 = game_objects[obj_oncheck]->getBoundingRect();
                
                // getting the x coordinates of each rectangle
                double x_left1 = rect1.getPosition().x, x_right1 = rect1.getPosition().x + rect1.getSize().x;
                double x_left2 = rect2.getPosition().x, x_right2 = rect2.getPosition().x + rect2.getSize().x;
                // and y coordinate
                double y_left1 = rect1.getPosition().y, y_right1 = rect1.getPosition().y + rect1.getSize().y;
                double y_left2 = rect2.getPosition().y, y_right2 = rect2.getPosition().y + rect2.getSize().y;

                // an intersection is considered found if the segments on the x and y axes intersect.
                // Since the function counts only the touch of the smaller segment of the larger one, it 
                // should be called for two cases. In one of them, the segment will be less than or equal 
                // to the second
                if ((largerIntersects(x_left1, x_right1, x_left2, x_right2) || largerIntersects(x_left2, x_right2, x_left1, x_right1)) &&
                    (largerIntersects(y_left1, y_right1, y_left2, y_right2) || largerIntersects(y_left2, y_right2, y_left1, y_right1))) {
                    auto center_rect1 = rect1.getPosition();
                    auto center_rect2 = rect2.getPosition();

                    center_rect1.x = center_rect1.x + (rect1.getSize().x / 2);
                    center_rect1.y = center_rect1.y + (rect1.getSize().y / 2);
                    center_rect2.x = center_rect2.x + (rect2.getSize().x / 2);
                    center_rect2.y = center_rect2.y + (rect2.getSize().y / 2);

                    // comparing the coordinates of the rectangles, 
                    // we can conclude about the mutual location between them.
                    // The handler call is called for two cases, on the x and y axis
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

void SGameEngine::HandleTiming(double elapsed) {

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

void SGameEngine::DeleteObjects() {
    if (delete_list.empty()) return;
    for (auto& obj_name : delete_list) {
        game_objects.erase(std::remove_if(game_objects.begin(), game_objects.end(),
            [obj_name](std::shared_ptr<GameObject> obj) { return obj->getName() == obj_name; }),
            game_objects.end()
        );
    }
    delete_list.clear();
}

void SGameEngine::Start() {
    window.setActive(true);
    window.setKeyRepeatEnabled(false); // disable for better perfomance

    sf::Time elapsed;
    sf::Time lag = sf::milliseconds(0);
    
    while (window.isOpen())
    {
        {   // start of critical section
            std::unique_lock<std::mutex> lock(synch);
            elapsed = clock.restart();
            lag += elapsed; // measure time between frames
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
            while (lag.asMilliseconds() > UPDATE_RATE) {    // "catching up" with the correct state of the game
                Update();
                lag -= sf::milliseconds(UPDATE_RATE);
            }
            HandleTiming(elapsed.asMilliseconds());
            Render();
            DeleteObjects();
        }   // end of critical section

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(UPDATE_RATE / 2))); // 16 milliseconds ~= 60 fps
    }
}