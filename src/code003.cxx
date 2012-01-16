#include <cmath>
#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include <list>

#include <time.h>

#include "font.h"
#include "gl_dot.h"
#include "freetype_font.h"

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

timespec last_frame;
timespec cur_frame;

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

	ship_t() :
			x(0.0), y(0.0), orientation(0.0), xo(0.0), move_forward(false), move_backward(
					false), move_left(false), move_right(false) {
	}

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
		if(ship.xo < 0)
			ship.xo = 0;
		if(ship.xo > 90.0)
			ship.xo = 90.0;
	}
}

void motionnotify(XMotionEvent & ev) {
	if (ship.right_click) {
		int move = ev.x - ship.xpos;
		ship.orientation -= 1.0 * move;

		int ymove = ev.y - ship.ypos;
		ship.xo -= 1.0 * ymove;
		if(ship.xo < 0)
			ship.xo = 0;
		if(ship.xo > 90.0)
			ship.xo = 90.0;

		ship.xpos = ev.x;
		ship.ypos = ev.y;
	}
}

void DrawAQuad() {
	last_frame.tv_sec = cur_frame.tv_sec;
	last_frame.tv_nsec = cur_frame.tv_nsec;
	clock_gettime(CLOCK_MONOTONIC_RAW, &cur_frame);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 1.0, 0., 0., 0., 0., 1., 0.);

	glDisable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.);
	glVertex3f(-.75, -.75, 0.);
	glColor3f(0., 1., 0.);
	glVertex3f(.75, -.75, 0.);
	glColor3f(0., 0., 1.);
	glVertex3f(.75, .75, 0.);
	glColor3f(1., 1., 0.);
	glVertex3f(-.75, .75, 0.);
	glEnd();

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
		ship.y += 20.0 * elapsed_time * sin(ship.orientation * M_PI / 180.0);
		ship.x += 20.0 * elapsed_time * cos(ship.orientation * M_PI / 180.0);
	}

	if (ship.move_backward) {
		ship.y -= 20.0 * elapsed_time * sin(ship.orientation * M_PI / 180.0);
		ship.x -= 20.0 * elapsed_time * cos(ship.orientation * M_PI / 180.0);
	}

	if (ship.move_left) {
		if (ship.right_click) {
			ship.y += 20.0 * elapsed_time
					* cos(ship.orientation * M_PI / 180.0);
			ship.x -= 20.0 * elapsed_time
					* sin(ship.orientation * M_PI / 180.0);
		} else {
			ship.orientation += 30.0 * elapsed_time;
		}
	}

	if (ship.move_right) {
		if (ship.right_click) {
			ship.y -= 20.0 * elapsed_time
					* cos(ship.orientation * M_PI / 180.0);
			ship.x += 20.0 * elapsed_time
					* sin(ship.orientation * M_PI / 180.0);
		} else {
			ship.orientation -= 30.0 * elapsed_time;
		}
	}

	glPushMatrix();
	glRotated(ship.xo, 1.0, 0.0, 0.0);
	glRotated(-ship.orientation + 90.0, 0.0, 0.0, 1.0);
	glTranslated(-ship.x, -ship.y, 0.0);


	std::list<gl::object *>::iterator iter = world.begin();
	while (iter != world.end()) {
		(*iter)->render();
		++iter;
	}

	glPopMatrix();

	char buf[512];
	snprintf(buf, 31, "%f %f %f", ship.x, ship.y, elapsed_time);
	f->print(0.0, 0.0, buf);
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

	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput,
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
		world.push_front(new gl::dot(rand() % 200 - 100, rand() % 200 - 100));
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100., 100., -100., 100., -100., 100.);

	f = new gl::freetype_t("/usr/share/fonts/corefonts/arial.ttf", 8);

	clock_gettime(CLOCK_MONOTONIC_RAW, &cur_frame);


	while (1) {
		//DrawAQuad();


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

