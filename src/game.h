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

#ifndef GAMEAPP_H_
#define GAMEAPP_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>

#include "event_func.h"
#include "event_handler.h"
#include "font.h"
#include "rwave.h"
#include "scene.h"
#include "rstring.h"
#include "vcontrol.h"

class game: public event_func {
	int _argc;
	char **_argv;
protected:
	SDL_TimerID timer;
	bool done;

	font * f;
	scene * sce;
	rwave * w;
	rstring * s;

	vcontrol vc;

	event_handler * ehr;

public:
	// Constructor and destructor
	game(int argc, char **argv);
	virtual ~game(void);

	// Initialization functions
	void InitApp(void);
	void InitializeSDL(void);
	void InstallTimer(void);
	static Uint32 GameLoopTimer(Uint32 interval, void* param);

	// Cleanup functions
	void Cleanup(void);

	// Event-related functions
	void EventLoop(void);
	void HandleUserEvents(SDL_Event* event);

	// Game related functions
	void GameLoop(void);
	void RenderFrame(void);

	GLuint LoadImage(char const * name);

	void PrintScreen(const char * text);

	void process_events(SDL_Event const & ev);

};

typedef game* GameAppPtr;
typedef game** GameAppHandle;

const int RUN_GAME_LOOP = 1;

#endif /* GAMEAPP_H_ */
