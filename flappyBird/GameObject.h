#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Vector2f position;
	sf::RectangleShape bounding_rect;
	sf::CircleShape sprite;

public:
	GameObject();
	GameObject(float x, float y, float width, float height);

	void setPosition(sf::Vector2f new_pos);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	sf::CircleShape getSprite();

protected:
	virtual void Update();	// calling each frame
	virtual void HandleInput(sf::Event input);	// calling each frame

	friend class SGameEngine;
};