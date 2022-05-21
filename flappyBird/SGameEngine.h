#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "SFML/Window.hpp"
#include <thread>
#include <time.h>


// main class, contents game objects and logic of engine
class SGameEngine {
private:
	sf::RenderWindow window;
	std::vector<std::shared_ptr<GameObject>> game_objects;

	void HandleInput(sf::Event input);
	void Update();
	void Render();

public:
	SGameEngine();
	void Start();
	void addObject(std::shared_ptr<GameObject> p_obj);
};