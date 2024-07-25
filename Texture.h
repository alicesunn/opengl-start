#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include <string>
#include <iostream>

class Texture {
public:
	Texture(std::string imagePath, bool configWrapAndFilter = false, bool flipVertical = false, bool hasAlpha = false) {
		// generate and bind texture object
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);

		// config wrapping and filtering options
		if (configWrapAndFilter) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // never set mipmap on magnify
		}

		// load image from file
		stbi_set_flip_vertically_on_load(flipVertical);
		unsigned char* imgData = stbi_load(imagePath.c_str(), &mImgWidth, &mImgHeight, &mImgChannels, 0);
		if (!imgData) {
			std::cout << "(generateTexture, Texture.h) "
				<< "ERROR: Failed to load texture '" << imagePath << ".'" << std::endl;
			return;
		}

		// generate actual texture
		GLenum format = (hasAlpha) ? (GL_RGBA) : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mImgWidth, mImgHeight, 0, format, GL_UNSIGNED_BYTE, imgData);
		glGenerateMipmap(GL_TEXTURE_2D); // auto-generate mipmap

		// clean up
		stbi_image_free(imgData);
	};

	unsigned int getTexture() const { return mTexture; }

private:
	unsigned int mTexture = 0;
	int mImgWidth = 0;
	int mImgHeight = 0;
	int mImgChannels = 0; // number of color channels
};

#endif