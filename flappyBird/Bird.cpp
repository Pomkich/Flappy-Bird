#include "Bird.h"

Bird::Bird(std::shared_ptr<FlappyBird> e_ptr) {
	game_over = false;
	engine_ptr = e_ptr;
	sf::Vector2f move_vector(0, 0);
	sf::Vector2f velocity(0, cvelocity);
	moving_vectors.push_back(move_vector);
	moving_vectors.push_back(velocity);
}

void Bird::Update() {
	PhisicalObject::Update();	// call object moving

	if (!game_over) {
		moving_vectors[0].y += moving_vectors[1].y;	// the influence of gravity
	}
}

void Bird::HandleInput(sf::Event input) {
	if (input.type == sf::Event::KeyPressed && input.key.code == sf::Keyboard::Space) {
		if (!game_over) {
			moving_vectors[0].y = impulse;
		}
	}
}

void Bird::onCollide(std::shared_ptr<GameObject> obj_col, Side side) {
	if (!game_over && obj_col->getType() == static_cast<int>(Type::pipe)) {
		game_over = true;
		engine_ptr.lock()->GameOver();
		deleteAllVectors();
	}
	else {
		engine_ptr.lock()->deleteObject("123");
	}
	//moving_vectors[0].y = 0;
	//moving_vectors[1].y = 0;
}