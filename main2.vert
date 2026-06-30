#version 330 core
layout (location = 0) in vec3 bPos;
layout (location = 1) in vec3 bColor;

out vec3 color2;
//uniform mat4 transform2;

void main()
{
	gl_Position = vec4(bPos, 1.0);
	color2 = bColor;


}
