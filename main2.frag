#version 330 core
out vec4 frag2Color;
in vec3 color2;

void main()
{
	frag2Color = vec4(color2, 1.0);

}