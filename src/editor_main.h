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

#ifndef EDITOR_MAIN_H_
#define EDITOR_MAIN_H_

#include <string>
#include "palette_window.h"
#include "gtk_gl.h"
#include "config.h"

class editor_main {
	GtkWidget * window_;
	GtkWidget * menubar_;
	GtkWidget * menubar_item_;
	GtkWidget * vbox_;

	GtkWidget * file_menu_item_;
	GtkWidget * check_menu_item_;
	GtkWidget * radio_menu_item_;

	GtkWidget * eventbox_;

	GtkWidget * file_menu_;
	GtkWidget * view_menu_;
	GtkWidget * select_menu_;


	GtkWidget * load_map_menu_;
	GtkWidget * save_map_menu_;
	GtkWidget * new_map_menu_;
	GtkWidget * quit_menu_;

	GtkWidget * check_layer_0_;
	GtkWidget * check_layer_1_;
	GtkWidget * check_layer_2_;
	GtkWidget * check_layer_3_;
	GtkWidget * check_layer_4_;
	GtkWidget * check_layer_5_;
	GtkWidget * check_layer_6_;
	GtkWidget * check_layer_7_;

	GtkWidget * radio_layer_0_;
	GtkWidget * radio_layer_1_;
	GtkWidget * radio_layer_2_;
	GtkWidget * radio_layer_3_;
	GtkWidget * radio_layer_4_;
	GtkWidget * radio_layer_5_;
	GtkWidget * radio_layer_6_;
	GtkWidget * radio_layer_7_;

	GtkObject * vajustement_;
	GtkObject * hajustement_;
	GtkWidget * scrolled_window_;

	GdkGC * gc_;

	GSList * radio_list_;

	glmap * map_;
	gtk_gl * gl_widget_;

	config * conf_;

	uint32_t selected_layer;

	palette_window * pl;

	std::string default_path_;

	int x_last, y_last;

public:
	editor_main(config * conf);
	virtual ~editor_main();

	void show();
	static void button_press_event(GtkWidget * widget, GdkEventButton * event,
			editor_main * ths);
	static void button_release_event(GtkWidget * widget, GdkEventButton * event,
			editor_main * ths);
	static void motion_notify_event(GtkWidget * widget, GdkEventButton * event,
			editor_main * ths);

	static void quit_menu_activate(GtkWidget * w, editor_main * ths);
	static void save_map_menu_activate(GtkWidget * w, editor_main * ths);
	static void load_map_menu_activate(GtkWidget * w, editor_main * ths);
	static void new_map_menu_activate(GtkWidget * w, editor_main * ths);
	static void destroy(GtkWidget *widget, gpointer data);

	static gboolean radio_menu_active(GtkWidget * w, editor_main * ths);
	static gboolean check_menu_active(GtkWidget * w, editor_main * ths);
	static void radio_active(GtkWidget * data, gpointer user_data);

	static gboolean gl_configure(GtkWidget * da, GdkEventConfigure *event,
			editor_main * ths);
};

#endif /* EDITOR_MAIN_H_ */
