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

#include <GL/gl.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "gtk_gl.h"

gtk_gl::gtk_gl(config * conf) {

	is_configured = FALSE;
	this->conf = conf;
	draw_area = gtk_drawing_area_new();
	//gtk_widget_set_events(draw_area, GDK_EXPOSURE_MASK);
	/* prepare GL */
	gl_config = gdk_gl_config_new_by_mode((GdkGLConfigMode)(GDK_GL_MODE_RGBA|GDK_GL_MODE_DOUBLE|GDK_GL_MODE_DEPTH));
	if (!gtk_widget_set_gl_capability(draw_area, gl_config, NULL, TRUE,
			GDK_GL_RGBA_TYPE)) {
		g_assert_not_reached ();
	}

	g_print("gtk_gl::gtk_gl\n");

	g_signal_connect (draw_area, "configure-event",
			G_CALLBACK (gtk_gl::configure), this);
	g_signal_connect (draw_area, "expose-event",
			G_CALLBACK (gtk_gl::expose), this);

}

gboolean gtk_gl::expose(GtkWidget * da, GdkEventExpose * event, gtk_gl * ths) {

	g_print("gtk_gl::expose\n");

	GdkGLContext * gl_context = gtk_widget_get_gl_context(da);
	GdkGLDrawable * gl_drawable = gtk_widget_get_gl_drawable (da);
	if (!gdk_gl_drawable_gl_begin(gl_drawable, gl_context)) {
		g_assert_not_reached ();
	}

	/* init pending objects */
	ths->gl_init_objects();
	/* draw in here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* render object */
	ths->gl_render_objects();

	glFlush();
	if (gdk_gl_drawable_is_double_buffered(gl_drawable))
		gdk_gl_drawable_swap_buffers(gl_drawable);
	gdk_gl_drawable_gl_end(gl_drawable);
	return TRUE;
}

gboolean gtk_gl::configure(GtkWidget * da, GdkEventConfigure *event,
		gtk_gl * ths) {
	printf("gtk_gl::configure\n");

	GdkGLContext * gl_context = gtk_widget_get_gl_context(da);
	GdkGLDrawable * gl_drawable = gtk_widget_get_gl_drawable (da);

	if (!gdk_gl_drawable_gl_begin(gl_drawable, gl_context)) {
		g_assert_not_reached ();
	}

	if (!ths->is_configured) {
		ilutRenderer(ILUT_OPENGL);
		ths->is_configured = TRUE;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, da->allocation.width,
			da->allocation.height);
	glOrtho(0, da->allocation.width,
			da->allocation.height, 0, -1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gdk_gl_drawable_gl_end(gl_drawable);
	return TRUE;
}

gboolean gtk_gl::realize(GtkWidget *da, gtk_gl * ths) {
	g_print("gtk_gl::realize");
	return TRUE;
}

GtkWidget * gtk_gl::get_draw_area() {
	return draw_area;
}

void gtk_gl::gl_add_object(gl_object * o) {
	pending_gl_init_elemts.push(o);
}

void gtk_gl::gl_render_objects() {
	std::list<gl_object *>::iterator iter;
	for (iter = elemts.begin(); iter != elemts.end(); iter++) {
		(*iter)->gl_render();
	}
}

void gtk_gl::gl_init_objects() {
	while (!pending_gl_init_elemts.empty()) {
		gl_object * o = pending_gl_init_elemts.front();
		o->gl_init();
		elemts.push_back(o);
		pending_gl_init_elemts.pop();
	}
}

