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

#ifndef GTK_GL_HPP_
#define GTK_GL_HPP_

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <gdk/gdkgl.h>
#include <list>
#include <queue>
#include "glmap.h"
#include "config.h"
#include "gl_object.h"

class gtk_gl {
public:
	GtkWidget * draw_area;
	GdkGLConfig * gl_config;

	glmap * map;
	config * conf;

	std::queue<gl_object *> pending_gl_init_elemts;
	std::list<gl_object *> elemts;

	gboolean is_configured;

	gtk_gl(config * conf);

	GtkWidget * get_draw_area();

	static gboolean expose(GtkWidget *da, GdkEventExpose *event,
			gtk_gl * ths);
	static gboolean configure(GtkWidget *da, GdkEventConfigure *event,
			gtk_gl * ths);
	static gboolean realize(GtkWidget *da, gtk_gl * ths);

	void gl_add_object(gl_object *);
	void gl_remove_object(gl_object *);

	void gl_render_objects();
	void gl_init_objects();

};

#endif /* GTK_GL_HPP_ */
