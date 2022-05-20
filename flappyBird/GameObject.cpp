#include "GameObject.h"

void GameObject::setPosition(sf::Vector2f new_pos) {
	position = new_pos;
}

sf::Vector2f GameObject::getPosition() {
	return position;
}