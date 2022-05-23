#pragma once
#include "SGameEngine.h"

class Bird;	// forward declaration

class FlappyBird : public SGameEngine, public std::enable_shared_from_this<FlappyBird> {
private:
	int current_pipe;
	std::shared_ptr<Bird> bird;
	std::vector<std::shared_ptr<GameObject>> pipes;

public:
	FlappyBird();

	void Init();

	void Restart();
};