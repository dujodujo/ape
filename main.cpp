#include <SDL.h>
#include <SDL_image.h>

#include "System.h"
#include "Surface.h"
#include "Globals.h"
#include "Type.h"
#include "VideoManager.h"
#include "Game.h"
#include "Color.h"
#include <iostream>


int main(int argc, char** argv) {
	InputEvent* event;
	bool quit = false;

	System::init();

	Game* game = new Game();
	Surface* root_surface;
	root_surface = new Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	while(!quit) {
		event = InputEvent::get_event();
		if(event != NULL) {
			if(event->is_window_closing()) {
		        quit = true;
	        } else if(event->is_keyboard_key_pressed()) {
		        if(event->get_keyboard_key() == InputEvent::KEY_ESCAPE)
			        quit = true;
		    }
			if(game != NULL)
		        game->notify_input(*event);
		    delete event;
	    }
		
		System::update();
		if(game != NULL)
	        game->update();

		root_surface->fill_with_color(Color::get_white());
		if(game != NULL)
		   game->display(*root_surface);
	
		VideoManager::get_instance()->display(*root_surface);
	}

	delete root_surface;
	delete game;

    
	System::quit();
	return 0;
}

