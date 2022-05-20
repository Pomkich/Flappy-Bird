#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height) {
	position.x = x;
	position.y = y;
	bounding_rect.setPosition(sf::Vector2f(x, y));
	bounding_rect.setSize(sf::Vector2f(width, height));
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setRadius(20);
}

void GameObject::Update() {

}

void GameObject::setPosition(sf::Vector2f new_pos) {
	position = new_pos;
}

sf::Vector2f GameObject::getPosition() {
	return position;
}

sf::CircleShape GameObject::getSprite() {
	return sprite;
}