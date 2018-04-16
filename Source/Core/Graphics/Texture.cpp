#pragma once
#include "Texture.h"
#include <string>
#include <assert.h>
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace kodi {

	// TODO: Do not just assume all the textures are going to be Texture 2D. Pass that as a parameter.

	Texture::Texture(const char * imagePath) {

		int width, height, nrChannels;
		GLenum channelToLoadImageAs;
		stbi_set_flip_vertically_on_load(true);

		unsigned char * data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

#if _DEBUG
		assert(NULL != data);
#endif

		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_);	// set texture wrapping to GL_REPEAT (default wrapping method)
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		switch (nrChannels)
		{
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		default:
#if _DEBUG
			assert("Unknown Channel" + nrChannels);
#endif
			channelToLoadImageAs = GL_RGBA;
			break;
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		// Free it after creating the texture.
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);

	}

	void Texture::Use() {

		// TODO: Check if the ID Exists or not.
#if _DEBUG
		assert(NULL != this);
#endif
		glBindTexture(GL_TEXTURE_2D, this->textureID);

	}

	Texture::~Texture() {
		glDeleteTextures(1, &textureID);
	}

}