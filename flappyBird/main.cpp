#include <iostream>
#include "SGameEngine.h"

using namespace std;

class Player : public GameObject {
public:
	float x; 
	Player() {
		x = 10.0;
	};

protected:
	virtual void Update() override {
		setPosition(sf::Vector2f(x, 100));
		x += 1;
		//if()
	}
};

int main() {
	SGameEngine game;

	game.addObject(std::make_shared<GameObject>(100, 100, 100, 100));
	game.addObject(std::make_shared<Player>());

	game.Start();

	return 0;
}