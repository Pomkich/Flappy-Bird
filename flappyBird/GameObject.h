#pragma once
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

class GameObject {
protected:
	std::string name; // name must be unique
	sf::Vector2f position;
	sf::RectangleShape bounding_rect;	// used in collision detection
	sf::Texture texture;
	sf::Sprite sprite;
	//sf::RectangleShape sprite;	// should be real sprite
	int type;	// interpretation falls on the shoulders of the developer

public:
	GameObject();
	GameObject(std::string nm);
	GameObject(std::string nm, float x, float y, float width, float height);

	void setPosition(sf::Vector2f new_pos);
	void setPosition(float x, float y);
	void setSize(sf::Vector2f size);
	void setSize(float x, float y);
	void setName(std::string nm);
	void setType(int tp);
	void setTexture(std::string text_path);

	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	sf::RectangleShape getBoundingRect();
	std::string getName();
	int getType();
	~GameObject();

protected:
	virtual void Update();	// calling each frame
	virtual void HandleInput(sf::Event input);	// calling each frame
	virtual void onCollide(std::shared_ptr<GameObject> obj_col, Side side);	// it is necessary to specify the side with which the collision occurred

	friend class SGameEngine;
};