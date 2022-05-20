#include <iostream>
#include "SGameEngine.h"

using namespace std;

int main() {
	SGameEngine game;

	game.addObject(std::make_shared<GameObject>(100, 100, 100, 100));

	game.Start();

	return 0;
}