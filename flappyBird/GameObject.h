#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class GameObject {
private:
	sf::Vector2f position;
	sf::RectangleShape bounding_rect;

public:
	void setPosition(sf::Vector2f new_pos);
	sf::Vector2f getPosition();

protected:
	virtual void Update() = 0;
};