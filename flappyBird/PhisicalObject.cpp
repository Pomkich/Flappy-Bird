#include "PhisicalObject.h"

PhisicalObject::PhisicalObject() {

}

void PhisicalObject::Update() {
	if (moving_vectors.empty()) return;

	float sum_x = 0, sum_y = 0;
	for (auto& vec : moving_vectors) {
		sum_x += vec.x;
		sum_y += vec.y;
	}
	setPosition(position.x + sum_x, position.y + sum_y);
}

void PhisicalObject::addVector(sf::Vector2f vec) {
	moving_vectors.push_back(vec);
}