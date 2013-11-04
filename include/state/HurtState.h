#ifndef HURT_STATE_H
#define HURT_STATE_H

#include "State.h"

class Hero::HurtState : public Hero::State {

private:
	const Rectangle source_xy;			/** coordinates of whatever is hurting hero */
	uint32_t end_hurt_date;				/** date when state ends */

public:
	HurtState(Hero& hero, const Rectangle& source_xy);
	~HurtState();

	void start(State* previous_state);
	void stop(State* next_state);
	void update();
};


#endif