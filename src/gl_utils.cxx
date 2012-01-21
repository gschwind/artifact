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

#include "gl_utils.h"
#include <stdlib.h>
#include <string>
#include <map>

gl_utils::gl_utils() {
	// TODO Auto-generated constructor stub

}

gl_utils::~gl_utils() {
	// TODO Auto-generated destructor stub
}

GLuint gl_utils::load_texture(char const * name) {
	static std::map<std::string, GLuint> data;

	if (data.count(name)) {
		return data[name];
	} else {

		ILuint texid;
		GLuint image;
		ilGenImages(1, &texid); /* Generation of one image name */
		ilBindImage(texid); /* Binding of image name */
		ILboolean success = ilLoadImage(name); /* Loading of image "image.jpg" */
		if (success) /* If no error occured: */
		{
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); /* Convert every colour component into
			 unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
			if (!success) {
				/* Error occured */
				exit(-1);
				return -1;
			}
			glGenTextures(1, &image); /* Texture name generation */
			glBindTexture(GL_TEXTURE_2D, image); /* Binding of texture name */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /* We will use linear
			 interpolation for magnification filter */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /* We will use linear
			 interpolation for minifying filter */
			printf("%d, %d, %d, %d\n", ilGetInteger(IL_IMAGE_BPP),
					ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
					ilGetInteger(IL_IMAGE_FORMAT));
			glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP),
					ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
					0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
					ilGetData()); /* Texture specification */
		} else {
			/* Error occured */
			exit(-1);
			return -1;
		}
		ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data
		 we can release memory used by image. */

		data[name] = image;
		return image;
	}
}

gl::freetype_t * gl_utils::load_font(char const * name, unsigned int size) {
	static std::map<std::pair<unsigned int, std::string>, gl::freetype_t *> data;
	std::pair<unsigned int, std::string> p(size, name);
	if (data.count(p)) {
		return data[p];
	} else {
		gl::freetype_t * f = new gl::freetype_t(name, size);
		data[p] = f;
		return f;
	}
}
