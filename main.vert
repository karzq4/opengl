#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aTexCoord2;

//out vec4 vertexColor; // specify a color output to the fragment shader 
out vec3 ourColor;
out vec3 position;
out vec2 texCoord;
out vec2 texCoord2;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	gl_Position = projection * view * model * vec4(aPos.x,aPos.y,aPos.z, 1.0); // see how we directly give a vec3 to vec4's constructor
	ourColor = aColor;
	position = aPos;
	texCoord = aTexCoord;
	texCoord2 = aTexCoord2;
	//vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a color (red dark in this occurance)

}




