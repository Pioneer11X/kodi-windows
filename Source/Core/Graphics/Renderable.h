#pragma once

#define GLEW_STATIC
#include <GL\glew.h>

namespace kodi {

	namespace graphics {

		// ఇది అన్ని Renderable objectlakoo vuntundhi.
		// Idhi chaalaavarakoo virtual ayyi vuntundhi. Manam dheeninundi extend chesukontaamu.
		class Renderable {

		private:
			// Vertex Buffer, Vertex Array inkaa, Element Buffer Objectlu.
			GLuint VBO, VAO, EBO;
			
		public:
			Renderable();
			~Renderable();

		};

	}

}

