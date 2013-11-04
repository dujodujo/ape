#include "PlayerMovementState.h"
#include "StraightMovement.h"
#include "PlayerMovement.h"
#include "HurtState.h"
#include "Geometry.h"
#include "System.h"
#include "Game.h"

Hero::HurtState::HurtState(Hero& hero, const Rectangle& source_xy) : 
	State(hero),
	source_xy(source_xy),
	end_hurt_date(0) {

}

Hero::HurtState::~HurtState() {}

void Hero::HurtState::start(State* previous_state) {
	State::start(previous_state);

	hero.set_animation_hurt();
	//hero.blinking();
	double angle = Geometry::get_angle(source_xy.get_x(), source_xy.get_y(), hero.get_x(), hero.get_y());
	StraightMovement* movement = new StraightMovement(angle, 120);
	hero.set_movement(movement);
	this->end_hurt_date = System::now() + 200;
}

void Hero::HurtState::stop(State* next_state) {
	State::stop(next_state);
	hero.clear_movement();
}

void Hero::HurtState::update() {
	State::update();
	if(hero.get_movement()->is_finished()) {
		hero.clear_movement();
		hero.set_movement(new PlayerMovement(hero.walking_speed));
		hero.set_state(new PlayerMovementState(hero));
	}
}