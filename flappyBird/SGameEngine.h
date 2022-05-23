#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "SFML/Window.hpp"
#include <iostream>
#include <thread>
#include <mutex>


// main class, contents game objects and logic of engine
class SGameEngine {
private:
	std::mutex synch;	// need to access the list of objects
	sf::RenderWindow window;
	std::vector<std::shared_ptr<GameObject>> game_objects;
	sf::Clock clock;	// needs to measure time betwean flames

	void HandleInput(sf::Event input);
	void CheckCollision();
	void Update();
	void Render();

public:
	SGameEngine();
	void Start();
	void addObject(std::shared_ptr<GameObject> p_obj);
	void deleteObject(std::string obj_name);
};