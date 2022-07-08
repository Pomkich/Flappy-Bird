#include "FlappyBird.h"
#include "Bird.h"

FlappyBird::FlappyBird() {
	srand(time(NULL));
}

void FlappyBird::HandleTiming(double elapsed) {
	// check all events
 	for (auto& time_event : events) {
		int id; double timing; void (FlappyBird::*method_ptr)();
		std::tie(id, timing, method_ptr) = time_event;	// unpack elements of tuple
		if (timing < 0) {	// if time expires, call function
			(shared_from_this().get()->*method_ptr)();	
			event_delete_list.push_back(id);	// link event to delete
		}
		else {	// else decrease timing
			std::get<1>(time_event) -= elapsed;
		}
	}

	// delete events, that has called higher
	for (auto& delete_id : event_delete_list) {
		events.erase(std::remove_if(events.begin(), events.end(),
			[delete_id](std::tuple<int, double, void (FlappyBird::*)()> ev) { 
				return delete_id == std::get<0>(ev); 
			}),
		events.end());
	}

	event_delete_list.clear();
}

void FlappyBird::addEvent(double time, void (FlappyBird::*method_ptr)()) {
	events.push_back(std::make_tuple(event_id, time, method_ptr));
	event_id++;
}

void FlappyBird::Restart() {
	std::cout << "restarted" << std::endl;

	current_pipe = 0;

	bird = std::make_shared<Bird>(shared_from_this());
	bird->setPosition(bird_start_x, bird_start_y);
	bird->setSize(bird_size, bird_size);
	bird->setName("bird");
 	bird->setTexture("sprites/bird.png");
	//bird->addVector(sf::Vector2f(0, -4)); // velocity

	for (int i = 0; i < 4; i++) {
		auto new_pipe = std::make_shared<PhisicalObject>();
		new_pipe->setName("up_pipe" + std::to_string(i));
		new_pipe->setTexture("sprites/pipe_up.png");
		new_pipe->setPosition(800, 0);
		new_pipe->setSize(pipe_width, pipe_height);
		new_pipe->addVector(sf::Vector2f(pipe_speed, 0));
		up_pipes.push_back(new_pipe);
		addObject(new_pipe);
	}

	for (int i = 0; i < 4; i++) {
		auto new_pipe = std::make_shared<PhisicalObject>();
		new_pipe->setName("bottom_pipe" + std::to_string(i));
		new_pipe->setTexture("sprites/pipe_bottom.png");
		new_pipe->setPosition(800, pipe_height + pipe_division);
		new_pipe->setSize(pipe_width, pipe_height);
		new_pipe->addVector(sf::Vector2f(pipe_speed, 0));
		bottom_pipes.push_back(new_pipe);
		addObject(new_pipe);
	}

	addObject(bird);
	addEvent(2000, &FlappyBird::ReplacePipe);
}

void FlappyBird::ReplacePipe() {
	if (current_pipe == 4) current_pipe = 0;
	up_pipes[current_pipe]->setPosition(800, -(rand() % 400));
	bottom_pipes[current_pipe]->setPosition(800, 
		up_pipes[current_pipe]->getPosition().y + pipe_division + pipe_height);
	current_pipe++;
	addEvent(2000, &FlappyBird::ReplacePipe);
}

void FlappyBird::ClearGame() {
	for (auto it = up_pipes.begin(); it != up_pipes.end(); it++) {
		deleteObject((*it)->getName());
	}
	for (auto it = bottom_pipes.begin(); it != bottom_pipes.end(); it++) {
		deleteObject((*it)->getName());
	}
	up_pipes.clear();
	bottom_pipes.clear();

	deleteObject(bird->getName());
	bird.reset();
}

void FlappyBird::GameOver() {
	for (int i = 0; i < 4; i++) {
		up_pipes[i]->deleteAllVectors();	// stop all pipes
		bottom_pipes[i]->deleteAllVectors();
	}
	events.clear();	// delete all events of last game

	addEvent(2000, &FlappyBird::ClearGame);
	addEvent(2100, &FlappyBird::Restart);
}