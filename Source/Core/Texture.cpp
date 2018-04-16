#pragma once
#include "Texture.h"
#include <string>
#include "stb_image.h"
#include <assert.h>
#include <GL/glew.h>

namespace kodi {

	// TODO: Do not just assume all the textures are going to be Texture 2D. Pass that as a parameter.

	Texture::Texture(const char * imagePath) {

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);

		unsigned char * data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

#if _DEBUG
		assert(NULL != data);
#endif

		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Free it after creating the texture.
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);

	}

	void Texture::Use() {

		glBindTexture(GL_TEXTURE_2D, this->textureID);

	}

	Texture::~Texture() {
		glDeleteTextures(1, &textureID);
	}

}