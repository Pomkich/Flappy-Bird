#include "FlappyBird.h"
#include "Bird.h"

FlappyBird::FlappyBird() {
	
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

void FlappyBird::Init() {
	bird = std::make_shared<Bird>(shared_from_this());
}

void FlappyBird::Restart() {
	std::cout << "restarting..." << std::endl;
}