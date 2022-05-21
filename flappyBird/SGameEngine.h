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
	std::list<std::shared_ptr<GameObject>> game_objects;

	void HandleInput(sf::Event input);
	void Update();
	void Render();

public:
	SGameEngine();
	void Start();
	void addObject(std::shared_ptr<GameObject> p_obj);
};