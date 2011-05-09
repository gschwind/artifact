/*
 * map.h
 *
 *  Created on: Jan 24, 2010
 *      Author: gschwind
 */

#ifndef MAP_H_
#define MAP_H_

#include <gtk/gtk.h>
#include <stdint.h>
#include <string>

class map {
protected:
	std::string filename_;
	std::string palette_name_;
	uint32_t width_, height_;
	uint8_t * data_;
	GdkGC * gc_;

public:
	map(std::string map_file);
	map(uint32_t width, uint32_t height, uint8_t fill, std::string palette_name);
	virtual ~map();

	virtual void set(uint32_t x, uint32_t y, uint32_t layer, uint8_t value);
	uint8_t get(uint32_t x, uint32_t y, uint32_t layer);
	void save_map(std::string file_name);
	void read_map(std::string file_name);
	std::string get_palette_name();

};

#endif /* MAP_H_ */
