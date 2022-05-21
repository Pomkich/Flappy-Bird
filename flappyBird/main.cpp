#include <iostream>
#include "SGameEngine.h"

using namespace std;

class Player : public GameObject {
public:
	Player() {
	};

protected:
	virtual void HandleInput(sf::Event input) override {
		if (input.type == sf::Event::KeyPressed) {
			switch (input.key.code) {

			case sf::Keyboard::Right:
				moving_vector.x = 5;
				break;
			case sf::Keyboard::Left:
				moving_vector.x = -5;
				break;
			case sf::Keyboard::Up:
				moving_vector.y = -5;
				break;
			case sf::Keyboard::Down:
				moving_vector.y = 5;
				break;
			}
		}
		else if (input.type == sf::Event::KeyReleased) {
			switch (input.key.code) {

			case sf::Keyboard::Right:
				moving_vector.x = 0;
				break;
			case sf::Keyboard::Left:
				moving_vector.x = 0;
				break;
			case sf::Keyboard::Up:
				moving_vector.y = 0;
				break;
			case sf::Keyboard::Down:
				moving_vector.y = 0;
				break;
			}
		}
	}
};

int main() {
	SGameEngine game;

	game.addObject(std::make_shared<GameObject>(100, 100, 100, 100));
	game.addObject(std::make_shared<Player>());

	game.Start();

	return 0;
}