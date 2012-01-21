/*
 * Copyright 2012 Benoit Gschwind <gschwind@gnu-log.net>
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

#include <cmath>
#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include <list>

#include <sys/types.h>
#include <time.h>

#include "font.h"
#include "gl_dot.h"
#include "freetype_font.h"
#include "gl_ship.h"
#include "ui_toolbar.h"
#include "ui_player_status.h"
#include "ui_target_status.h"

Display * dpy;
Window root;
GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 8, GLX_DOUBLEBUFFER, None };
XVisualInfo *vi;
Colormap cmap;
XSetWindowAttributes swa;
Window win;
GLXContext glc;
XWindowAttributes gwa;
XEvent xev;

std::list<gl::object *> world;

std::list<gl::ship_t *> enemy;

timespec last_frame;
timespec cur_frame;

gl::toolbar * toolbar;

gl::status_player * left_status_player;
gl::status_target * right_status_target;

struct ship_t {
	double x, y;
	double orientation;
	double xo;
	bool move_forward;
	bool move_backward;
	bool move_left;
	bool move_right;
	bool right_click;
	int xpos, ypos;

	double max_shield;
	double max_armor;
	double max_hull;

	double shield;
	double armor;
	double hull;

	double zoom;

	GLuint texture;

	ship_t() :
			x(0.0), y(0.0), orientation(0.0), xo(0.0), move_forward(false), move_backward(
					false), move_left(false), move_right(false), zoom(10.0) {
		max_shield = 100.0;
		shield = 100.0;
	}

	double foox, fooy;
	long long int foos;

	gl::ship_t * selected;

};

ship_t ship;

gl::freetype_t * f;

void keypress(XKeyEvent * ev) {
	//char *s = XKeysymToString(XKeycodeToKeysym(dpy, ev->keycode, 0));
	//printf("%s\n", s);

	KeySym k = XKeycodeToKeysym(dpy, ev->keycode, 0);

	if (k == XK_w) {
		ship.move_forward = true;
		printf("press\n");
	} else if (k == XK_s) {
		ship.move_backward = true;
	} else if (k == XK_a) {
		ship.move_left = true;
	} else if (k == XK_d) {
		ship.move_right = true;
	} else if (k == XK_Escape) {
		glXMakeCurrent(dpy, None, NULL);
		glXDestroyContext(dpy, glc);
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
		exit(0);
	}
}

void keyrelease(XKeyEvent * ev) {

	/* detect auto repeat, this method is probably
	 * implementation-dependant,
	 * We recommand to disable auto repeat widely
	 */

	XEvent xev;
	if (XCheckMaskEvent(dpy, KeyPressMask, &xev)) {
		if (xev.xkey.keycode == ev->keycode && xev.xkey.time == ev->time) {
			/* a short key press after the first one, ignore this release. */
			return;
		} else {
			XPutBackEvent(dpy, &xev);
		}
	}

	KeySym k = XKeycodeToKeysym(dpy, ev->keycode, 0);
	if (k == XK_w) {
		ship.move_forward = false;
		printf("release\n");
	} else if (k == XK_s) {
		ship.move_backward = false;
	} else if (k == XK_a) {
		ship.move_left = false;
	} else if (k == XK_d) {
		ship.move_right = false;
	}
}

void buttonpress(XButtonEvent & ev) {
	if (ev.button == Button3) {
		ship.right_click = true;
		ship.xpos = ev.x;
		ship.ypos = ev.y;
	}
}

void buttonrelease(XButtonEvent & ev) {
	if (ev.button == Button3) {
		ship.right_click = false;
		int move = ev.x - ship.xpos;
		ship.orientation -= 1.0 * move;
		int ymove = ev.y - ship.ypos;
		ship.xo -= 1.0 * ymove;
		if (ship.xo < 0)
			ship.xo = 0;
		if (ship.xo > 90.0)
			ship.xo = 90.0;
	} else if (ev.button == Button4) {
		ship.zoom += 1.0;
		if (ship.zoom > 10.0) {
			ship.zoom = 10.0;
		}
	} else if (ev.button == Button5) {
		ship.zoom -= 1.0;
		if (ship.zoom < 1.0) {
			ship.zoom = 1.0;
		}
	} else if (ev.button == Button1) {

		double x = ev.x - 400.0;
		double y = 300.0 - ev.y;

		// x => x * cos(r) + y * sin(r)
		// y => x * sin(r) + y * cos(r)

		ship.foox = x * cos(-ship.orientation * M_PI / 180.0) * 10.0 / ship.zoom
				+ y * sin(-ship.orientation * M_PI / 180.0) * 10.0 / ship.zoom
				+ ship.x;
		ship.fooy = x * -sin(-ship.orientation * M_PI / 180.0) * 10.0
				/ ship.zoom
				+ y * cos(-ship.orientation * M_PI / 180.0) * 10.0 / ship.zoom
				+ ship.y;

		gl::ship_t * i = 0;
		double min_d = 1.0e20;

		std::list<gl::ship_t *>::iterator iter_x = enemy.begin();
		while (iter_x != enemy.end()) {
			//printf("(%f,%f) (%f,%f)\n", (*iter_x)->x, (*iter_x)->y, ship.foox,
			//		ship.fooy);
			double xx = (*iter_x)->x - ship.foox;
			double yy = (*iter_x)->y - ship.fooy;
			double d = xx * xx + yy * yy;
			if (d < min_d) {
				min_d = d;
				i = (*iter_x);
			}
			(*iter_x)->is_selected = false;
			++iter_x;
		}

		ship.selected = 0;
		right_status_target->target = 0;
		//printf("i: %f\n", min_d);
		if (sqrt(min_d) < 12.0) {
			ship.foos = (long long int) i;
			i->is_selected = true;
			ship.selected = i;
			right_status_target->target = i;
		}

	}
}

void motionnotify(XMotionEvent & ev) {
	if (ship.right_click) {
		int move = ev.x - ship.xpos;
		ship.orientation -= 1.0 * move;

		int ymove = ev.y - ship.ypos;
		ship.xo -= 1.0 * ymove;
		if (ship.xo < 0)
			ship.xo = 0;
		if (ship.xo > 90.0)
			ship.xo = 90.0;

		ship.xpos = ev.x;
		ship.ypos = ev.y;
	}
}

void DrawAQuad() {
	last_frame.tv_sec = cur_frame.tv_sec;
	last_frame.tv_nsec = cur_frame.tv_nsec;
	clock_gettime(4, &cur_frame);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400., 400., -300., 300., -100., 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 1.0, 0., 0., 0., 0., 1., 0.);

	glPushMatrix();
	glScaled(ship.zoom / 10.0, ship.zoom / 10.0, 1.0);
	//glRotated(ship.xo, 1.0, 0.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glDisable(GL_COLOR);
	glBindTexture(GL_TEXTURE_2D, ship.texture);
	glBegin(GL_QUADS);
	glTexCoord2d(1., 1.);
	glColor3f(1., 1., 1.);
	glVertex3f(-16.0, -16., 0.);
	glTexCoord2d(0., 1.);
	glVertex3f(16.0, -16.0, 0.);
	glTexCoord2d(0., 0.);
	glVertex3f(16.0, 16.0, 0.);
	glTexCoord2d(1., 0.);
	glVertex3f(-16.0, 16.0, 0.);
	glEnd();

	glPopMatrix();

	/* diff time */
	/* curtime = cur_frame.tv_sec + cur_frame.tv_nsec * 1e-9
	 * lasttime = last_frame.tv_sec + last_frame.tv_nsec * 1e-9
	 *
	 * elapsed = cur - last;
	 * elapsed = (cur_frame.tv_sec + cur_frame.tv_nsec * 1e-9) - (last_frame.tv_sec + last_frame.tv_nsec * 1e-9)
	 * elapsed = (cur_frame.tv_sec - last_frame.tv_sec) + (cur_frame.tv_nsec - last_frame.tv_nsec) * 1e-9
	 * if there is smal among of time elapsed between this two time elapsed time will be accurate.
	 *
	 * the following method is accurate for small elapsed time (double is about 10e-15 accuracy between 0 and 1)
	 *
	 */
	timespec diff;
	diff.tv_sec = cur_frame.tv_sec - last_frame.tv_sec;
	diff.tv_nsec = cur_frame.tv_nsec - last_frame.tv_nsec;
	double elapsed_time = (diff.tv_nsec * 1.0e-9) + diff.tv_sec;

	if (ship.move_forward) {
		ship.y += 100.0 * elapsed_time * cos(ship.orientation * M_PI / 180.0);
		ship.x -= 100.0 * elapsed_time * sin(ship.orientation * M_PI / 180.0);

	}

	if (ship.move_backward) {
		ship.y -= 100.0 * elapsed_time * cos(ship.orientation * M_PI / 180.0);
		ship.x += 100.0 * elapsed_time * sin(ship.orientation * M_PI / 180.0);

	}

	if (ship.move_left) {
		if (ship.right_click) {
			ship.y -= 100.0 * elapsed_time
					* sin(ship.orientation * M_PI / 180.0);
			ship.x -= 100.0 * elapsed_time
					* cos(ship.orientation * M_PI / 180.0);
		} else {
			ship.orientation += 50.0 * elapsed_time;
		}
	}

	if (ship.move_right) {
		if (ship.right_click) {
			ship.y += 100.0 * elapsed_time
					* sin(ship.orientation * M_PI / 180.0);
			ship.x += 100.0 * elapsed_time
					* cos(ship.orientation * M_PI / 180.0);
		} else {
			ship.orientation -= 50.0 * elapsed_time;
		}
	}

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glScaled(ship.zoom / 10.0, ship.zoom / 10.0, 1.0);
	//glRotated(ship.xo, 1.0, 0.0, 0.0);
	glRotated(-ship.orientation, 0.0, 0.0, 1.0);
	glTranslated(-ship.x, -ship.y, 0.0);

	std::list<gl::object *>::iterator iter = world.begin();
	while (iter != world.end()) {
		(*iter)->render();
		++iter;
	}

	glBegin(GL_LINES);
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(10.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 10.0, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 10.0);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	std::list<gl::ship_t *>::iterator iter_x = enemy.begin();
	while (iter_x != enemy.end()) {
		(*iter_x)->render();
		++iter_x;
	}

	glPopMatrix();

	glPushMatrix();
	char buf[512];
	snprintf(buf, 511, "%f %f %f %f", ship.x, ship.y, ship.orientation,
			elapsed_time);
	f->print(10.0, 560.0, buf);
	snprintf(buf, 511, "%f %f %lld", ship.foox, ship.fooy, ship.foos);
	f->print(10.0, 580.0, buf);

	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0., 800., 0., 600., -100., 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0., 0., 1., 0.);



//	glColor3d(1.0, 1.0, 1.0);
//	glPushMatrix();
//	glTranslated(100.0, 50.0, 0.0);
//	f->print2("Shield");
//	glTranslated(0.0, -11.0, 0.0);
//	f->print2("Armor");
//	glTranslated(0.0, -11.0, 0.0);
//	f->print2("Hull");

	glPopMatrix();

	glPushMatrix();
	glTranslated(200.0, 0.0, 0.0);
	toolbar->render();
	glPopMatrix();

	glPushMatrix();
	glTranslated(200.0, 100.0, 0.0);
	left_status_player->render();
	glPopMatrix();

	glPushMatrix();
	glTranslated(450.0, 100.0, 0.0);
	right_status_target->render();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINES);
	glColor3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(10.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 10.0, 0.0);
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 10.0);
	glEnd();

	//glFlush();
}

#define MyEventMask (ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask)

int main(int argc, char *argv[]) {

	dpy = XOpenDisplay(NULL);

	/* disable auto repeat on serveur */
	//XAutoRepeatOn(dpy);
	if (dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(0);
	}

	root = DefaultRootWindow(dpy);

	vi = glXChooseVisual(dpy, 0, att);

	if (vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(0);
	} else {
		printf("\n\tvisual %p selected\n", (void *) vi->visualid);
	}/* %p creates hexadecimal output like in glxinfo */

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.event_mask = MyEventMask;

	win = XCreateWindow(dpy, root, 0, 0, 800, 600, 0, vi->depth, InputOutput,
			vi->visual, CWColormap | CWEventMask, &swa);

	XMapWindow(dpy, win);
	XStoreName(dpy, win, "VERY SIMPLE APPLICATION");

	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	ilInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
	/* enable alpha */
	//glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < 1000; ++i) {
		world.push_front(new gl::dot(rand() % 1000 - 500, rand() % 1000 - 500));
	}

	ship.texture = gl_utils::load_texture("data/mytest.png");
	toolbar = new gl::toolbar();
	left_status_player = new gl::status_player();
	right_status_target = new gl::status_target();

	right_status_target->max_shield = 100.0;
	right_status_target->max_armor = 100;
	right_status_target->max_hull = 100;
	right_status_target->shield = 100.0;
	right_status_target->armor = 100;
	right_status_target->hull = 100;

	left_status_player->max_shield = 100.0;
	left_status_player->max_armor = 100;
	left_status_player->max_hull = 100;
	left_status_player->shield = 100.0;
	left_status_player->armor = 100;
	left_status_player->hull = 100;

	for (int i = 0; i < 10; ++i) {
		char buf[100];
		snprintf(buf, 99, "enemy%03d", i);
		std::string t = buf;
		enemy.push_front(
				new gl::ship_t((double)(rand() % 1000 - 500), (double)(rand() % 1000 - 500),
						(double)(rand() % 3600) / 10.0, t));
		enemy.front()->texture = ship.texture;
	}

	f = gl_utils::load_font("data/DejaVuSans.ttf", 11);

	clock_gettime(4, &cur_frame);

	while (1) {

		DrawAQuad();
		glXSwapBuffers(dpy, win);

		while (XCheckMaskEvent(dpy, ~NoEventMask, &xev)) {
			if (xev.type == Expose) {

			} else if (xev.type == KeyPress) {
				keypress(&xev.xkey);
			} else if (xev.type == KeyRelease) {
				keyrelease(&xev.xkey);
			} else if (xev.type == ButtonPress) {
				buttonpress(xev.xbutton);
			} else if (xev.type == ButtonRelease) {
				buttonrelease(xev.xbutton);
			} else if (xev.type == MotionNotify) {
				motionnotify(xev.xmotion);
			}
		}

		//printf("looop\n");
		//XGetWindowAttributes(dpy, win, &gwa);
		//glViewport(0, 0, gwa.width, gwa.height);
		//DrawAQuad();
		//glXSwapBuffers(dpy, win);

	} /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */

