/*
 * map.cc
 *
 *  Created on: Jan 24, 2010
 *      Author: gschwind
 */

#include "map.h"

#define FILE_TAG 280958

struct map_file_head {
	uint32_t file_tag;
	uint32_t width;
	uint32_t heigth;
	uint32_t pallette_name_length;
};

map::map(std::string map_file) {
	data_ = 0;
	read_map(map_file);
}

map::map(uint32_t width, uint32_t height, uint8_t fill, std::string palette_name) {
	uint8_t * data;
	palette_name_ = palette_name;
	data = new uint8_t[width * height * 8];
	for(int i = 0; i < width * height * 8; i++)
		data[i] = fill;
	data_ = data;
	width_ = width;
	height_ = height;
	filename_ = "";
}

map::~map() {
	if(data_)
		delete[] data_;
}

void map::set(uint32_t x, uint32_t y, uint32_t layer, uint8_t value) {
	data_[layer * width_ * height_ + y * width_ + x] = value;
}
uint8_t map::get(uint32_t x, uint32_t y, uint32_t layer) {
	return data_[layer * width_ * height_ + y * width_ + x];
}

void map::save_map(std::string file_name) {
	map_file_head head;
	head.file_tag = FILE_TAG;
	head.width = width_;
	head.heigth = height_;
	head.pallette_name_length = palette_name_.length();
	FILE * f = fopen(file_name.c_str(), "wb");
	fwrite(&head, sizeof(map_file_head), 1, f);
	fwrite(palette_name_.c_str(), sizeof(uint8_t), head.pallette_name_length, f);
	fwrite(data_, sizeof(uint8_t), head.width * head.heigth * 8, f);
	fclose(f);
}

/* read a map file */
void map::read_map(std::string file_name) {
	map_file_head head;
	int8_t * palette_name;
	uint8_t * data;
	FILE * f = fopen(file_name.c_str(), "rb");
	fread(&head, sizeof(map_file_head), 1, f);
	palette_name = new int8_t[sizeof(int8_t) * head.pallette_name_length + 1];
	fread(palette_name, sizeof(uint8_t), head.pallette_name_length, f);
	palette_name[head.pallette_name_length] = 0;
	palette_name_ = reinterpret_cast<char *>(palette_name);
	delete[] palette_name;
	data = new uint8_t[sizeof(uint8_t) * head.width * head.heigth * 8];
	fread(data, sizeof(uint8_t), head.width * head.heigth * 8, f);
	if(data_)
		delete[] data_;
	data_ = data;
	width_ = head.width;
	height_ = head.heigth;
	filename_ = file_name;
	fclose(f);
}

std::string map::get_palette_name() {
	return palette_name_;
}

