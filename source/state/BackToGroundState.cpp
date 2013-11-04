#include "PlayerMovementState.h"
#include "BackToGroundState.h"
#include "TargetMovement.h"
#include "MapEntities.h"
#include "Rectangle.h"
#include "System.h"
#include "Map.h"

Hero::BackToGroundState::BackToGroundState(Hero& hero, uint32_t end_delay) :
  State(hero),
  end_delay(end_delay),
  end_date(0) {
	  this->target_xy.set_xy(hero.last_ground_coordinates);
}

Hero::BackToGroundState::~BackToGroundState() {}

void Hero::BackToGroundState::start(State* previous_state) {
	State::start(previous_state);

	//hero.set_movement(new TargetMovement(100, 100, 144));
	hero.set_xy(target_xy);
	hero.set_animation_stopped();
	hero.set_state(new PlayerMovementState(hero));
}

void Hero::BackToGroundState::stop(State* next_state) {
	State::stop(next_state);

	//hero.clear_movement();
}

void Hero::BackToGroundState::update() {
	State::update();

	if(hero.get_movement()->is_finished()) {
		//hero.set_state(new PlayerMovementState(hero));
	}
}