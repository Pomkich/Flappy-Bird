#pragma once
#include <list>
#include <memory>
#include "GameObject.h"


class SGameEngine {
public:
	void addObject(std::unique_ptr<GameObject> p_obj);

private:
	std::list<std::unique_ptr<GameObject>> game_objects;

	SGameEngine();
	void Update();
	void Render();
};