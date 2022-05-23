#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "SFML/Window.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <list>


// main class, contents game objects and logic of engine
class SGameEngine {
private:
	std::mutex synch;	// need to access the list of objects
	sf::RenderWindow window;
	std::vector<std::shared_ptr<GameObject>> game_objects;
	sf::Clock clock;	// needs to measure time betwean flames
	std::list<std::string> delete_list;	// you cannot delete objects in the middle of the game cycle, so we need to delay their removal

	void HandleInput(sf::Event input);
	void CheckCollision();
	void Update();
	void Render();
	void DeleteObjects();	// called in end of game loop

public:
	SGameEngine();
	void Start();
	void addObject(std::shared_ptr<GameObject> p_obj);
	void deleteObject(std::string obj_name);
};