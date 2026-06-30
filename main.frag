#version 330 core
out vec4 fragColor;
in vec3 ourColor;
in vec3 position;
in vec2 texCoord;
in vec2 texCoord2;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float opacity;

//in vec4 vertexColor; // the input variable from the vertex shader (same name and same type) 

//uniform vec4 ourColor; // we set this variable in the opengl code

void main()
{
		//fragColor = vertexColor;
		fragColor = mix(texture(ourTexture, texCoord), texture(ourTexture2, texCoord2), opacity);

}