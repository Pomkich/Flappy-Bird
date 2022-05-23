#include "GameObject.h"

GameObject::GameObject() {
	int x = 0, y = 0, width = 0, height = 0;
	type = 0;
	name = "Undefined";
	position.x = x;
	position.y = y;
	bounding_rect.setPosition(sf::Vector2f(x, y));
	bounding_rect.setSize(sf::Vector2f(width, height));
	sprite.setSize(sf::Vector2f(width, height));
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(sf::Vector2f(x, y));
}

GameObject::GameObject(std::string nm) {
	int x = 0, y = 0, width = 0, height = 0;
	type = 0;
	name = nm;
	position.x = x;
	position.y = y;
	bounding_rect.setPosition(sf::Vector2f(x, y));
	bounding_rect.setSize(sf::Vector2f(width, height));
	sprite.setSize(sf::Vector2f(width, height));
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(sf::Vector2f(x, y));
}

GameObject::GameObject(std::string nm, float x, float y, float width, float height) {
	type = 0;
	name = nm;
	position.x = x;
	position.y = y;
	bounding_rect.setPosition(sf::Vector2f(x, y));
	bounding_rect.setSize(sf::Vector2f(width, height));
	sprite.setSize(sf::Vector2f(width, height));
	sprite.setFillColor(sf::Color::Green);
	sprite.setPosition(sf::Vector2f(x, y));
}

void GameObject::setPosition(sf::Vector2f new_pos) {
	position = new_pos;
	bounding_rect.setPosition(new_pos);
	sprite.setPosition(new_pos);
}

void GameObject::setPosition(float x, float y) {
	sf::Vector2f new_pos(x, y);
	position = new_pos;
	bounding_rect.setPosition(new_pos);
	sprite.setPosition(new_pos);
}

void GameObject::setSize(sf::Vector2f size) {
	bounding_rect.setSize(size);
	sprite.setSize(size);
}

void GameObject::setSize(float x, float y) {
	sf::Vector2f size(x, y);
	bounding_rect.setSize(size);
	sprite.setSize(size);
}

void GameObject::setName(std::string nm) {
	name = nm;
}

void GameObject::setType(int tp) {
	type = tp;
}

sf::Vector2f GameObject::getPosition() {
	return position;
}

sf::RectangleShape GameObject::getSprite() {
	return sprite;
}

sf::RectangleShape GameObject::getBoundingRect() {
	return bounding_rect;
}

std::string GameObject::getName() {
	return name;
}

int GameObject::getType() {
	return type;
}

void GameObject::Update() {

}

void GameObject::HandleInput(sf::Event input) {

}

void GameObject::onCollide(std::shared_ptr<GameObject> obj_col, Side side) {

}

GameObject::~GameObject() {
	std::cout << "deleted object: " << name << std::endl;
}