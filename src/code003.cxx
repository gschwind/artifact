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
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <list>

#include <sys/types.h>
#include <time.h>

#include "global.h"
#include "gl_main_ship.h"
#include "font.h"
#include "gl_dot.h"
#include "freetype_font.h"
#include "gl_ship.h"
#include "ui_toolbar.h"
#include "ui_player_status.h"
#include "ui_target_status.h"
#include "gl_shoot_anim.h"
#include "gl_cast_bar.h"

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

void keypress(XKeyEvent * ev) {
	//char *s = XKeysymToString(XKeycodeToKeysym(dpy, ev->keycode, 0));
	//printf("%s\n", s);

	KeySym k = XKeycodeToKeysym(dpy, ev->keycode, 0);

	if (k == XK_w) {
		global.ship.move_forward = true;
		printf("press\n");
	} else if (k == XK_s) {
		global.ship.move_backward = true;
	} else if (k == XK_a) {
		global.ship.move_left = true;
	} else if (k == XK_d) {
		global.ship.move_right = true;
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
		global.ship.move_forward = false;
		printf("release\n");
	} else if (k == XK_s) {
		global.ship.move_backward = false;
	} else if (k == XK_a) {
		global.ship.move_left = false;
	} else if (k == XK_d) {
		global.ship.move_right = false;
	} else if (k == XK_1) {
		if (global.ship.selected) {

			if (global.ship.casting == 0) {
				global.ship.casting = new gl::cast_bar(1.0, global.ship.x,
						global.ship.y, global.ship.selected->x,
						global.ship.selected->y, global.ship.selected);
			}

//			if (global.ship.selected->shield > 0.0) {
//				global.ship.selected->shield -= 10.0;
//			} else if (global.ship.selected->armor > 0.0) {
//				global.ship.selected->armor -= 10.0;
//			} else if (global.ship.selected->hull > 0.0) {
//				global.ship.selected->hull -= 10.0;
//			}
//
//			global.world.push_back(
//					new gl::shoot_anim_t(global.ship.x, global.ship.y,
//							global.ship.selected->x, global.ship.selected->y));
//
//			if (global.ship.selected->hull <= 0) {
//				global.world.remove(global.ship.selected);
//				global.enemy.remove(global.ship.selected);
//				delete global.ship.selected;
//				global.ship.selected = 0;
//				global.right_status_target->target = 0;
//			}



		}
	} else if (k == XK_2) {

	} else if (k == XK_3) {

	} else if (k == XK_4) {

	} else if (k == XK_5) {

	} else if (k == XK_6) {

	} else if (k == XK_7) {

	} else if (k == XK_8) {

	} else if (k == XK_9) {

	} else if (k == XK_0) {

	} else if (k == XK_Tab) {
		double x = global.ship.x;
		double y = global.ship.y;

		gl::ship_t * i = 0;
		double min_d = 1.0e20;

		std::list<gl::ship_t *>::iterator iter_x = global.enemy.begin();
		while (iter_x != global.enemy.end()) {
			//printf("(%f,%f) (%f,%f)\n", (*iter_x)->x, (*iter_x)->y, ship.foox,
			//		ship.fooy);
			double xx = (*iter_x)->x - x;
			double yy = (*iter_x)->y - y;
			double d = xx * xx + yy * yy;
			if (d < min_d) {
				min_d = d;
				i = (*iter_x);
			}
			(*iter_x)->is_selected = false;
			++iter_x;
		}

		if(global.ship.casting) {
			delete global.ship.casting;
			global.ship.casting = 0;
		}

		global.ship.selected = 0;
		global.right_status_target->target = 0;
		//printf("i: %f\n", min_d);
		if (sqrt(min_d) < 250.0) {
			global.ship.foos = (long long int) i;
			i->is_selected = true;
			global.ship.selected = i;
			global.right_status_target->target = i;
		}

	} else if (k == XK_space) {

		if(global.ship.casting) {
			delete global.ship.casting;
			global.ship.casting = 0;
		}

	}
}

void buttonpress(XButtonEvent & ev) {
	if (ev.button == Button3) {
		global.ship.right_click = true;
		global.ship.xpos = ev.x;
		global.ship.ypos = ev.y;
	} else if (ev.button == Button1) {
		global.ship.left_click = true;
	}
}

void buttonrelease(XButtonEvent & ev) {
	if (ev.button == Button3) {
		global.ship.right_click = false;
		int move = ev.x - global.ship.xpos;
		global.ship.orientation -= 1.0 * move;
		int ymove = ev.y - global.ship.ypos;
		global.ship.xo -= 1.0 * ymove;
		if (global.ship.xo < 0)
			global.ship.xo = 0;
		if (global.ship.xo > 90.0)
			global.ship.xo = 90.0;
	} else if (ev.button == Button4) {
		global.ship.zoom += 1.0;
		if (global.ship.zoom > 10.0) {
			global.ship.zoom = 10.0;
		}
	} else if (ev.button == Button5) {
		global.ship.zoom -= 1.0;
		if (global.ship.zoom < 1.0) {
			global.ship.zoom = 1.0;
		}
	} else if (ev.button == Button1) {
		global.ship.left_click = false;

		if (!global.ship.right_click) {
			double x = ev.x - 400.0;
			double y = 300.0 - ev.y;

			// x => x * cos(r) + y * sin(r)
			// y => x * sin(r) + y * cos(r)

			global.ship.foox = x * cos(-global.ship.orientation * M_PI / 180.0)
					* 10.0 / global.ship.zoom
					+ y * sin(-global.ship.orientation * M_PI / 180.0) * 10.0
							/ global.ship.zoom + global.ship.x;
			global.ship.fooy = x * -sin(-global.ship.orientation * M_PI / 180.0)
					* 10.0 / global.ship.zoom
					+ y * cos(-global.ship.orientation * M_PI / 180.0) * 10.0
							/ global.ship.zoom + global.ship.y;

			gl::ship_t * i = 0;
			double min_d = 1.0e20;

			std::list<gl::ship_t *>::iterator iter_x = global.enemy.begin();
			while (iter_x != global.enemy.end()) {
				//printf("(%f,%f) (%f,%f)\n", (*iter_x)->x, (*iter_x)->y, ship.foox,
				//		ship.fooy);
				double xx = (*iter_x)->x - global.ship.foox;
				double yy = (*iter_x)->y - global.ship.fooy;
				double d = xx * xx + yy * yy;
				if (d < min_d) {
					min_d = d;
					i = (*iter_x);
				}
				(*iter_x)->is_selected = false;
				++iter_x;
			}

			if(global.ship.casting) {
				delete global.ship.casting;
				global.ship.casting = 0;
			}

			global.ship.selected = 0;
			global.right_status_target->target = 0;
			//printf("i: %f\n", min_d);
			if (sqrt(min_d) < 12.0) {
				global.ship.foos = (long long int) i;
				i->is_selected = true;
				global.ship.selected = i;
				global.right_status_target->target = i;
			}

		}

	}
}

void motionnotify(XMotionEvent & ev) {
	if (global.ship.right_click) {
		int move = ev.x - global.ship.xpos;
		global.ship.orientation -= 1.0 * move;

		int ymove = ev.y - global.ship.ypos;
		global.ship.xo -= 1.0 * ymove;
		if (global.ship.xo < 0)
			global.ship.xo = 0;
		if (global.ship.xo > 90.0)
			global.ship.xo = 90.0;

		global.ship.xpos = ev.x;
		global.ship.ypos = ev.y;
	}
}

void draw_circle(double r, double step) {
	glBegin(GL_LINES);
	glColor3d(0.4, 0.4, 0.4);
	int i;
	double rstep = M_PI * 2.0 / step;
	for (i = 0; i < step; i += 2) {
		glVertex3d(cos(i * rstep) * r, sin(i * rstep) * r, 0.0);
		glVertex3d(cos((i + 1) * rstep) * r, sin((i + 1) * rstep) * r, 0.0);
	}
	glEnd();
}

void render_axes() {
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
}

void render() {
	global.last_frame.tv_sec = global.cur_frame.tv_sec;
	global.last_frame.tv_nsec = global.cur_frame.tv_nsec;
	clock_gettime(4, &global.cur_frame);
	timespec diff;
	diff.tv_sec = global.cur_frame.tv_sec - global.last_frame.tv_sec;
	diff.tv_nsec = global.cur_frame.tv_nsec - global.last_frame.tv_nsec;

	double elapsed_time = (diff.tv_nsec * 1.0e-9) + diff.tv_sec;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* world render */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-400., 400., -300., 300., -100., 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 1.0, 0., 0., 0., 0., 1., 0.);

	glPushMatrix();
	glScaled(global.ship.zoom / 10.0, global.ship.zoom / 10.0, 1.0);
	//glRotated(ship.xo, 1.0, 0.0, 0.0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glDisable(GL_COLOR);
	glBindTexture(GL_TEXTURE_2D, global.ship.texture);
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

	{
		glDisable(GL_TEXTURE_2D);
		draw_circle(250.0, 100.0);
	}

	glPopMatrix();

	if (global.ship.move_forward
			|| (global.ship.left_click && global.ship.right_click)) {
		global.ship.y += 100.0 * elapsed_time
				* cos(global.ship.orientation * M_PI / 180.0);
		global.ship.x -= 100.0 * elapsed_time
				* sin(global.ship.orientation * M_PI / 180.0);

	}

	if (global.ship.move_backward) {
		global.ship.y -= 100.0 * elapsed_time
				* cos(global.ship.orientation * M_PI / 180.0);
		global.ship.x += 100.0 * elapsed_time
				* sin(global.ship.orientation * M_PI / 180.0);

	}

	if (global.ship.move_left) {
		if (global.ship.right_click) {
			global.ship.y -= 100.0 * elapsed_time
					* sin(global.ship.orientation * M_PI / 180.0);
			global.ship.x -= 100.0 * elapsed_time
					* cos(global.ship.orientation * M_PI / 180.0);
		} else {
			global.ship.orientation += 50.0 * elapsed_time;
		}
	}

	if (global.ship.move_right) {
		if (global.ship.right_click) {
			global.ship.y += 100.0 * elapsed_time
					* sin(global.ship.orientation * M_PI / 180.0);
			global.ship.x += 100.0 * elapsed_time
					* cos(global.ship.orientation * M_PI / 180.0);
		} else {
			global.ship.orientation -= 50.0 * elapsed_time;
		}
	}

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glScaled(global.ship.zoom / 10.0, global.ship.zoom / 10.0, 1.0);
	//glRotated(ship.xo, 1.0, 0.0, 0.0);
	glRotated(-global.ship.orientation, 0.0, 0.0, 1.0);
	glTranslated(-global.ship.x, -global.ship.y, 0.0);

	std::list<gl::renderable_i *>::iterator iter = global.world.begin();
	while (iter != global.world.end()) {
		(*iter)->render(elapsed_time);
		++iter;
	}

	render_axes();

	/* trick to resolve overloaded function */
	bool (*func)(gl::renderable_i *) = &gl::renderable_i::need_destroy;
	global.world.remove_if(func);

	glPopMatrix();

	glPushMatrix();
	glColor3d(1.0, 1.0, 1.0);
	char buf[512];
	snprintf(buf, 511, "%f %f %f %f", global.ship.x, global.ship.y,
			global.ship.orientation, elapsed_time);
	global.f->print(10.0, 560.0, buf);
	snprintf(buf, 511, "%f %f %lld", global.ship.foox, global.ship.fooy,
			global.ship.foos);
	global.f->print(10.0, 580.0, buf);

	glPopMatrix();

	/* UI render */
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
	global.toolbar->render();
	glPopMatrix();

	glPushMatrix();
	glTranslated(200.0, 100.0, 0.0);
	global.left_status_player->render();
	glPopMatrix();

	glPushMatrix();
	glTranslated(450.0, 100.0, 0.0);
	global.right_status_target->render();
	glPopMatrix();

	if (global.ship.casting) {
		glPushMatrix();
		glTranslated(350.0, 70.0, 0.0);
		global.ship.casting->render(elapsed_time);
		glPopMatrix();

		if(global.ship.casting->need_destroy()) {
			delete global.ship.casting;
			global.ship.casting = 0;
		}

	}



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
		global.world.push_front(
				new gl::dot(rand() % 1000 - 500, rand() % 1000 - 500));
	}

	global.ship.texture = gl_utils::load_texture("data/mytest.png");
	global.toolbar = new gl::toolbar();
	global.left_status_player = new gl::status_player();
	global.right_status_target = new gl::status_target();

	global.right_status_target->max_shield = 100.0;
	global.right_status_target->max_armor = 100;
	global.right_status_target->max_hull = 100;
	global.right_status_target->shield = 100.0;
	global.right_status_target->armor = 100;
	global.right_status_target->hull = 100;

	global.left_status_player->max_shield = 100.0;
	global.left_status_player->max_armor = 100;
	global.left_status_player->max_hull = 100;
	global.left_status_player->shield = 100.0;
	global.left_status_player->armor = 100;
	global.left_status_player->hull = 100;

	for (int i = 0; i < 10; ++i) {
		char buf[100];
		snprintf(buf, 99, "enemy%03d", i);
		std::string t = buf;
		global.enemy.push_front(
				new gl::ship_t((double) (rand() % 1000 - 500),
						(double) (rand() % 1000 - 500),
						(double) (rand() % 3600) / 10.0, t));
		global.enemy.front()->texture = global.ship.texture;
		global.world.push_front(global.enemy.front());
	}

	global.f = gl_utils::load_font("data/DejaVuSans.ttf", 11);

	clock_gettime(4, &global.cur_frame);

	while (1) {

		render();
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
		//render();
		//glXSwapBuffers(dpy, win);

	} /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */

