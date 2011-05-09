/*
 * Copyright 2010 Benoit Gschwind <gschwind@gnu-log.net>
 *
 * This file is part of artifact.
 *
 * artifact is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * artifact is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with artifact.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "game.h"
#include "config.h"

// Constructor
game::game(int argc, char **argv) : vc() {
	done = false;
	_argv = argv;
	_argc = argc;
	printf("%s\n", argv[0]);
}

// Destructor
game::~game(void) {

}

// Initialization functions
void game::InitApp(void) {
	InitializeSDL();
	InstallTimer();

	std::string sss(_argv[0]);
	sss += ".ini";
	config * c = new config(sss);
	ehr = new event_handler(*c, &vc);
	std::string sfont = c->get_config("datadir", "");
	sfont += "/lat1.png";
	f = new font(sfont.c_str(), 32, 8);
	sce = new scene();
	s = new rstring("Hello world!!!", f, 10, 10);
	w = new rwave(s, 0.1, 2.0);
	sce->add(w);
}

void game::InitializeSDL(void) {
	int error;
	SDL_Surface* drawContext;

	error = SDL_Init(SDL_INIT_EVERYTHING);

	// Create a double-buffered draw context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags;
	flags = SDL_OPENGL;
	drawContext = SDL_SetVideoMode(800, 600, 0, flags);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ilInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	glEnable(GL_TEXTURE_2D);
	/* enable alpha */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void game::InstallTimer(void) {
	timer = SDL_AddTimer(30, GameLoopTimer, this);
}

Uint32 game::GameLoopTimer(Uint32 interval, void* param) {
	// Create a user event to call the game loop.
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = RUN_GAME_LOOP;
	event.user.data1 = 0;
	event.user.data2 = 0;

	SDL_PushEvent(&event);

	return interval;
}

// Cleanup functions
void game::Cleanup(void) {
	SDL_bool success;
	success = SDL_RemoveTimer(timer);

	SDL_Quit();
}

// Event-related functions
void game::EventLoop(void) {
	SDL_Event event;

	while ((!done) && (SDL_WaitEvent(&event))) {
		switch (event.type) {
		case SDL_USEREVENT:
			HandleUserEvents(&event);
			break;
		case SDL_QUIT:
			done = true;
			break;
		default:
			ehr->process_events(event);
			break;
		} // End switch

	} // End while

}

void game::HandleUserEvents(SDL_Event* event) {
	switch (event->user.code) {
	case RUN_GAME_LOOP:
		GameLoop();
		break;

	default:
		break;
	}
}

// Game related functions
void game::GameLoop(void) {
	RenderFrame();
}

void game::RenderFrame(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7, 0.5, 0.8);
	glRectf(300.0, 100.0, 20.0, 20.0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);
	//glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 128.0);
	//glTexCoord2f(1.0, 0.0); glVertex2f(256, 128.0);
	//glTexCoord2f(1.0, 1.0); glVertex2f(256.0, 0.0);
	//glEnd();
	sce->render();
	SDL_GL_SwapBuffers();
}


void game::process_events(SDL_Event const & ev){
	switch (ev.type) {
	case SDL_KEYDOWN:
		printf("YESSS! %s\n", SDL_GetKeyName(ev.key.keysym.sym));
		break;
	case SDL_JOYBUTTONUP:
		printf("JOYBUTTONUP %d\n", ev.button.button);
		break;
	case SDL_JOYBUTTONDOWN:
		printf("JOYBUTTONDOWN %d\n", ev.button.button);
		break;
	case SDL_JOYAXISMOTION:
		printf("JOYAXISMOTION axis: %d value: %d\n", (int)ev.jaxis.axis, (int)ev.jaxis.value);
		if(ev.jaxis.axis == 4){
			if(ev.jaxis.value > 0) {
				s->x += 10;
			} else if (ev.jaxis.value < 0){
				s->x -= 10;
			}
		}
		break;
	} // End switch

}
