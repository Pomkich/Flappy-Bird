#include <iostream>
#include "SGameEngine.h"
#include "PhisicalObject.h"

using namespace std;

class Player : public PhisicalObject {
public:
	Player() {
		moving_vectors.push_back(sf::Vector2f(0, 0));	// there is two vectors for player
		moving_vectors.push_back(sf::Vector2f(0, 0));	// movement. Developer must remember what each vector means
	};

protected:
	virtual void HandleInput(sf::Event input) override {
		if (input.type == sf::Event::KeyPressed) {
			switch (input.key.code) {

			case sf::Keyboard::Right:
				moving_vectors[0].x = 5;
				break;
			case sf::Keyboard::Left:
				moving_vectors[1].x = -5;
				break;
			case sf::Keyboard::Up:
				moving_vectors[0].y = -5;
				break;
			case sf::Keyboard::Down:
				moving_vectors[1].y = 5;
				break;
			}
		}
		if (input.type == sf::Event::KeyReleased) {
			switch (input.key.code) {

			case sf::Keyboard::Right:
				moving_vectors[0].x = 0;
				break;
			case sf::Keyboard::Left:
				moving_vectors[1].x = 0;
				break;
			case sf::Keyboard::Up:
				moving_vectors[0].y = 0;
				break;
			case sf::Keyboard::Down:
				moving_vectors[1].y = 0;
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