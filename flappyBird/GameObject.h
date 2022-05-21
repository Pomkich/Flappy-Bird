#pragma once
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject {
protected:
	std::string name; // name must be unique
	sf::Vector2f position;
	sf::RectangleShape bounding_rect;	// used in collision detection
	sf::RectangleShape sprite;	// should be real sprite

public:
	GameObject();
	GameObject(std::string nm);
	GameObject(std::string nm, float x, float y, float width, float height);

	void setPosition(sf::Vector2f new_pos);
	void setPosition(float x, float y);
	void setSize(sf::Vector2f size);
	void setSize(float x, float y);
	void setName(std::string nm);

	sf::Vector2f getPosition();
	sf::RectangleShape getSprite();
	sf::RectangleShape getBoundingRect();
	std::string getName();
	~GameObject();

protected:
	virtual void Update();	// calling each frame
	virtual void HandleInput(sf::Event input);	// calling each frame

	friend class SGameEngine;
};