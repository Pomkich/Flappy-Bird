#pragma once
#include "SGameEngine.h"
#include "PhisicalObject.h"
#include <random>

class Bird;	// forward declaration

static int event_id = 0;

class FlappyBird : public SGameEngine, public std::enable_shared_from_this<FlappyBird> {
private:
	int current_pipe;
	int current_background;
	std::shared_ptr<Bird> bird;
	std::vector<std::shared_ptr<PhisicalObject>> up_pipes;
	std::vector<std::shared_ptr<PhisicalObject>> bottom_pipes;
	std::vector<std::shared_ptr<PhisicalObject>> backgrounds;
	// events, that would call after the expiration of time
	// first element of tuple - id, needed for identifying event and deleting him
	// second - timing. It decreases every iteration
	// third - pointer to the method to be called
	std::vector<std::tuple<int, double, void (FlappyBird::*)()>> events;
	std::list<int> event_delete_list;

	virtual void HandleTiming(double elapsed) override;

public:
	FlappyBird();

	void GameOver();
	void ClearGame();
	void Restart();
	void ReplacePipe();
	void ReplaceBackground();

	void addEvent(double time, void (FlappyBird::*method_ptr)());
};