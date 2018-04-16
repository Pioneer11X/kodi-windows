#pragma once

namespace kodi {

	class Texture
	{
	public:

		unsigned int textureID;

		Texture(const char * imagePath);

		void Use();

		~Texture();
	};

}
