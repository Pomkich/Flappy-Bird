#pragma once
#include "PhisicalObject.h"
#include "FlappyBird.h"
#include "GameConstants.h"

class Bird : public PhisicalObject {
private:
	bool game_over;
	std::weak_ptr<FlappyBird> engine_ptr;

public:
	Bird(std::shared_ptr<FlappyBird> e_ptr);

private:
	virtual void Update() override;
	virtual void HandleInput(sf::Event input) override;
	virtual void onCollide(std::shared_ptr<GameObject> obj_col, Side side) override;
};