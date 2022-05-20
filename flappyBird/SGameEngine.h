#pragma once
#include <list>
#include <memory>
#include "GameObject.h"
#include "SFML/Window.hpp"
#include <thread>
#include <time.h>


class SGameEngine {
	sf::RenderWindow window;

private:
	std::list<std::unique_ptr<GameObject>> game_objects;

	void Update();
	void Render();

public:
	SGameEngine();
	void Start();
	void addObject(std::unique_ptr<GameObject> p_obj);
};