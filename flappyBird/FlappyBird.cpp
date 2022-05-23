#include "FlappyBird.h"
#include "Bird.h"

FlappyBird::FlappyBird() {
	
}

void FlappyBird::Init() {
	bird = std::make_shared<Bird>(shared_from_this());
}

void FlappyBird::Restart() {

}