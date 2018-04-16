
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourSecondTexture;

void main()
{
    // FragColor = vec4(ourColor, 1.0f);
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = mix(texture(ourTexture, TexCoord), texture(ourSecondTexture, TexCoord), 0.2);
}


