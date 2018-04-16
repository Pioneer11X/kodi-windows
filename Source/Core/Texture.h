#pragma once

namespace kodi {

	class Texture
	{
	public:

		unsigned int textureID;

		// The Image Path is the file path and the format, is typically betweem RGBA and RGB.
		Texture::Texture(const char * imagePath);

		void Use();

		~Texture();
	};

}
