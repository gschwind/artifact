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

#include <gtk/gtk.h>
#include "editor_main.h"
#include "gtk_gl.h"
#include "config.h"

editor_main::editor_main(config * conf) {
	GdkColor black = { 0, 0, 0, 0 };

	x_last = -1;
	y_last = -1;

	gl_widget_ = new gtk_gl(conf);
	//map_ = new gtk_map(*conf, 100, 100, 255, "testbackground.png");
	map_ = new glmap(*conf, 100, 100, 2, "testbackground.png",
			gl_widget_->get_draw_area());
	gl_widget_->gl_add_object(map_);

	pl = new palette_window(*conf, map_);

	default_path_ = conf->get_config("datadir", "./");

	window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window_), "Map Editor");
	gtk_window_set_default_size(GTK_WINDOW(window_), 300, 300);
	gtk_container_set_border_width(GTK_CONTAINER(window_), 0);

	vbox_ = gtk_vbox_new(FALSE, 0);

	eventbox_ = gtk_event_box_new();

	/* Creation du menu */
	/* Creation du menu file */
	file_menu_ = gtk_menu_new();
	view_menu_ = gtk_menu_new();
	select_menu_ = gtk_menu_new();

	/* creation des elements du menu */
	new_map_menu_ = gtk_menu_item_new_with_label("New ...");
	load_map_menu_ = gtk_menu_item_new_with_label("Load ...");
	save_map_menu_ = gtk_menu_item_new_with_label("Save As ...");
	quit_menu_ = gtk_menu_item_new_with_label("Quit");

	check_layer_0_ = gtk_check_menu_item_new_with_label("cLayer 0");
	check_layer_1_ = gtk_check_menu_item_new_with_label("cLayer 1");
	check_layer_2_ = gtk_check_menu_item_new_with_label("cLayer 2");
	check_layer_3_ = gtk_check_menu_item_new_with_label("cLayer 3");
	check_layer_4_ = gtk_check_menu_item_new_with_label("cLayer 4");
	check_layer_5_ = gtk_check_menu_item_new_with_label("cLayer 5");
	check_layer_6_ = gtk_check_menu_item_new_with_label("cLayer 6");
	check_layer_7_ = gtk_check_menu_item_new_with_label("cLayer 7");

	radio_layer_0_ = gtk_radio_menu_item_new_with_label(0, "rLayer 0");
	radio_list_ = gtk_radio_menu_item_get_group(
			GTK_RADIO_MENU_ITEM(radio_layer_0_));
	selected_layer = 0;

	radio_layer_1_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_0_), "rLayer 1");
	radio_layer_2_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_1_), "rLayer 2");
	radio_layer_3_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_2_), "rLayer 3");
	radio_layer_4_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_3_), "rLayer 4");
	radio_layer_5_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_4_), "rLayer 5");
	radio_layer_6_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_5_), "rLayer 6");
	radio_layer_7_ = gtk_radio_menu_item_new_with_label_from_widget(
			GTK_RADIO_MENU_ITEM(radio_layer_6_), "rLayer 7");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (radio_layer_0_), TRUE);

	/* ajout des elements au menu */
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu_), new_map_menu_);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu_), load_map_menu_);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu_), save_map_menu_);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu_), quit_menu_);

	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_0_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_1_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_2_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_3_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_4_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_5_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_6_);
	gtk_menu_shell_append(GTK_MENU_SHELL(view_menu_), check_layer_7_);

	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_0_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_1_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_2_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_3_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_4_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_5_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_6_);
	gtk_menu_shell_append(GTK_MENU_SHELL(select_menu_), radio_layer_7_);

	/* creation de la bar des menus */
	menubar_ = gtk_menu_bar_new();

	/* creation des items de la bar des menu */
	file_menu_item_ = gtk_menu_item_new_with_label("File");
	radio_menu_item_ = gtk_menu_item_new_with_label("View");
	check_menu_item_ = gtk_menu_item_new_with_label("Select");

	/* ajout des elements de la bar des menus */
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar_), file_menu_item_);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar_), radio_menu_item_);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar_), check_menu_item_);

	/* liens des menus entres eux */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item_), file_menu_);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(radio_menu_item_), view_menu_);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(check_menu_item_), select_menu_);

	/* liens des actions liees aux menus */
	g_signal_connect(G_OBJECT(new_map_menu_), "activate",
			G_CALLBACK (editor_main::new_map_menu_activate), this);
	g_signal_connect(G_OBJECT(load_map_menu_), "activate",
			G_CALLBACK (editor_main::load_map_menu_activate), this);
	g_signal_connect(G_OBJECT(save_map_menu_), "activate",
			G_CALLBACK (editor_main::save_map_menu_activate), this);
	g_signal_connect(G_OBJECT(quit_menu_), "activate",
			G_CALLBACK (editor_main::quit_menu_activate), this);

	g_signal_connect(G_OBJECT(radio_layer_0_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_1_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_2_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_3_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_4_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_5_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_6_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);
	g_signal_connect(G_OBJECT(radio_layer_7_), "toggled",
			G_CALLBACK (editor_main::radio_menu_active), this);

	g_signal_connect(G_OBJECT(check_layer_0_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_1_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_2_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_3_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_4_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_5_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_6_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);
	g_signal_connect(G_OBJECT(check_layer_7_), "toggled",
			G_CALLBACK (editor_main::check_menu_active), this);

	//vajustement_ = gtk_adjustment_new(0, 0, 100, 1, 20, 25);
	//hajustement_ = gtk_adjustment_new(0, 0, 100, 1, 20, 25);
	scrolled_window_ = gtk_scrolled_window_new(0, 0);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window_),
			GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_placement(GTK_SCROLLED_WINDOW(scrolled_window_),
			GTK_CORNER_TOP_LEFT);

	g_signal_connect(G_OBJECT(eventbox_), "button_press_event",
			G_CALLBACK (editor_main::button_press_event), this);
	g_signal_connect(G_OBJECT(eventbox_), "button_release_event",
			G_CALLBACK (editor_main::button_release_event), this);
	g_signal_connect(G_OBJECT(eventbox_), "motion_notify_event",
			G_CALLBACK (editor_main::motion_notify_event), this);

	g_signal_connect (G_OBJECT(window_), "delete_event",
			G_CALLBACK (editor_main::destroy), NULL);

	gtk_container_add(GTK_CONTAINER(window_), vbox_);
	gtk_box_pack_start(GTK_BOX(vbox_), menubar_, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_), scrolled_window_, TRUE, TRUE, 0);
	gtk_scrolled_window_add_with_viewport(
			GTK_SCROLLED_WINDOW(scrolled_window_), eventbox_);
	gtk_container_add(GTK_CONTAINER(eventbox_), gl_widget_->get_draw_area());

}

editor_main::~editor_main() {

}

void editor_main::show() {
	pl->show();
	gtk_widget_show_all(window_);
}

void editor_main::button_press_event(GtkWidget * widget,
		GdkEventButton * event, editor_main * ths) {
	if (event->state & GDK_BUTTON1_MASK) {
		int select_x, select_y;
		select_x = ((int) event->x) / 16;
		select_y = ((int) event->y) / 16;
		ths->map_->set_pxl(event->x, event->y, ths->selected_layer,
				ths->pl->get_selected_sprite());
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	} else if (event->state & GDK_BUTTON3_MASK) {
		ths->x_last = event->x;
		ths->y_last = event->y;
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	}
	g_print("X: %f Y: %f B: %d\n", event->x, event->y, event->state);
}

void editor_main::button_release_event(GtkWidget * widget,
		GdkEventButton * event, editor_main * ths) {
	if (event->state & GDK_BUTTON1_MASK) {
		int select_x, select_y;
		select_x = ((int) event->x) / 16;
		select_y = ((int) event->y) / 16;
		ths->map_->set_pxl(event->x, event->y, ths->selected_layer,
				ths->pl->get_selected_sprite());
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	} else if (event->state & GDK_BUTTON3_MASK) {
		//ths->map_->move_view_pos(event->x - ths->x_last, event->y - ths->y_last);
		ths->x_last = -1;
		ths->y_last = -1;
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	}
	g_print("X: %f Y: %f B: %d\n", event->x, event->y, event->state);
}

void editor_main::motion_notify_event(GtkWidget * widget,
		GdkEventButton * event, editor_main * ths) {
	if (event->state & GDK_BUTTON1_MASK) {
		int select_x, select_y;
		select_x = ((int) event->x) / 16;
		select_y = ((int) event->y) / 16;
		ths->map_->set_pxl(event->x, event->y, ths->selected_layer,
				ths->pl->get_selected_sprite());
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	} else if (event->state & GDK_BUTTON3_MASK) {
		if (ths->x_last > 0 && ths->y_last > 0) {
		ths->map_->move_view_pos(ths->x_last - event->x, ths->y_last - event->y);
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
		}
		ths->x_last = event->x;
		ths->y_last = event->y;
	}
	g_print("X: %f Y: %f B: %d\n", event->x, event->y, event->state);
}

void editor_main::quit_menu_activate(GtkWidget * w, editor_main * ths) {
	gtk_main_quit();
}

void editor_main::save_map_menu_activate(GtkWidget * w, editor_main * ths) {
	GtkWidget * dialog;
	dialog = gtk_file_chooser_dialog_new("Save Map", GTK_WINDOW(ths->window_),
			GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL,
			GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);
	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER (dialog),
			TRUE);
	if (0) {
		gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (dialog),
				ths->default_path_.c_str());
		gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER (dialog),
				"unamed.map");
	} else {
		gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (dialog),
				ths->default_path_.c_str());
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER (dialog), "unamed.map");
	}

	if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
		ths->map_->save_map(filename);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);

}

void editor_main::load_map_menu_activate(GtkWidget * w, editor_main * ths) {
	GtkWidget *dialog;
	dialog = gtk_file_chooser_dialog_new("Open Map", GTK_WINDOW(ths->window_),
			GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL,
			GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
		ths->map_->read_map(filename);
		ths->map_->redraw();
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}

void editor_main::new_map_menu_activate(GtkWidget * w, editor_main * ths) {

}
/* Another callback */
void editor_main::destroy(GtkWidget *widget, gpointer data) {
	gtk_main_quit();
}

gboolean editor_main::radio_menu_active(GtkWidget * w, editor_main * ths) {
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(w))) {
		if (w == ths->radio_layer_0_)
			ths->selected_layer = 0;
		if (w == ths->radio_layer_1_)
			ths->selected_layer = 1;
		if (w == ths->radio_layer_2_)
			ths->selected_layer = 2;
		if (w == ths->radio_layer_3_)
			ths->selected_layer = 3;
		if (w == ths->radio_layer_4_)
			ths->selected_layer = 4;
		if (w == ths->radio_layer_5_)
			ths->selected_layer = 5;
		if (w == ths->radio_layer_6_)
			ths->selected_layer = 6;
		if (w == ths->radio_layer_7_)
			ths->selected_layer = 7;
	}
	return TRUE;
}

gboolean editor_main::check_menu_active(GtkWidget * w, editor_main * ths) {
	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(w))) {
		if (w == ths->check_layer_0_)
			ths->map_->show_layer(0);
		if (w == ths->check_layer_1_)
			ths->map_->show_layer(1);
		if (w == ths->check_layer_2_)
			ths->map_->show_layer(2);
		if (w == ths->check_layer_3_)
			ths->map_->show_layer(3);
		if (w == ths->check_layer_4_)
			ths->map_->show_layer(4);
		if (w == ths->check_layer_5_)
			ths->map_->show_layer(5);
		if (w == ths->check_layer_6_)
			ths->map_->show_layer(6);
		if (w == ths->check_layer_7_)
			ths->map_->show_layer(7);
		//ths->map_->redraw();
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	} else {
		if (w == ths->check_layer_0_)
			ths->map_->hide_layer(0);
		if (w == ths->check_layer_1_)
			ths->map_->hide_layer(1);
		if (w == ths->check_layer_2_)
			ths->map_->hide_layer(2);
		if (w == ths->check_layer_3_)
			ths->map_->hide_layer(3);
		if (w == ths->check_layer_4_)
			ths->map_->hide_layer(4);
		if (w == ths->check_layer_5_)
			ths->map_->hide_layer(5);
		if (w == ths->check_layer_6_)
			ths->map_->hide_layer(6);
		if (w == ths->check_layer_7_)
			ths->map_->hide_layer(7);
		//ths->map_->redraw();
		//gtk_widget_queue_draw(GTK_WIDGET(ths->map_->get_image()));
		gtk_widget_queue_draw(GTK_WIDGET(ths->gl_widget_->get_draw_area()));
	}
	return TRUE;
}

void editor_main::radio_active(GtkWidget * data, gpointer user_data) {
	if (data != user_data) {
		printf("toto\n");
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (data), FALSE);
	} else {
		printf("toto1\n");
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM (data), TRUE);
	}
}

gboolean editor_main::gl_configure(GtkWidget *da, GdkEventConfigure *event,
		editor_main * ths) {
	g_print("editor_main::gl_configure\n");
	ths->map_->set_size(da->allocation.height, da->allocation.width);
	return TRUE;
}
