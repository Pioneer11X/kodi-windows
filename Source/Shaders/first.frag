
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourSecondTexture;



void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(ourTexture, TexCoord), texture(ourSecondTexture, TexCoord), 0.2);
}


