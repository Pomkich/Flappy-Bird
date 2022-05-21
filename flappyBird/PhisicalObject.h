#pragma once
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include <vector>

class PhisicalObject : public GameObject {
protected:
	std::vector<sf::Vector2f> moving_vectors;

private:
	virtual void Update() override;

public:
	PhisicalObject();
	void addVector(sf::Vector2f vec);
};

