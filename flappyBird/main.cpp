#include <iostream>
#include "SGameEngine.h"
#include "PhisicalObject.h"

using namespace std;

class Player : public PhisicalObject {
public:
	Player() {
		moving_vectors.push_back(sf::Vector2f(0, 0));	// there is two vectors for player movement
		moving_vectors.push_back(sf::Vector2f(0, 0));	// developer must remember what each vector means
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

	virtual void onCollide(std::shared_ptr<GameObject> obj_col, Side side) override {
		cout << "collided: ";
		switch (side) {
		case Side::left:
			cout << "left";
			break;
		case Side::right:
			cout << "right";
			break;
		case Side::up:
			cout << "up";
			break;
		case Side::down:
			cout << "down";
			break;
		}
		cout << endl;
	}
};

int main() {
	SGameEngine game;

	game.addObject(std::make_shared<GameObject>("rect", 300, 100, 100, 100));
	
	{
		std::shared_ptr<Player> player = make_shared<Player>();
		player->setSize(100, 100);
		player->setName("player");
		game.addObject(player);
	}

	//game.deleteObject("rect");

	game.Start();


	return 0;
}