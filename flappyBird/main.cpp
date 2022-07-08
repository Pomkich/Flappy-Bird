#include <iostream>
#include "SGameEngine.h"
#include "PhisicalObject.h"
#include "FlappyBird.h"
#include "Bird.h"

using namespace std;


int main() {

	std::shared_ptr<FlappyBird> game = make_shared<FlappyBird>();

	game->addEvent(0, &FlappyBird::Restart);

	game->Start();

	return 0;
}