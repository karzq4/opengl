#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ShaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow*window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400, lastY = 300;
bool firstMouse = true;
float fov = 45.0f;
float yVelocity = 0.0f;
float gravity = 9.8f;




glm::vec3 cubePositiobs[] =
{
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};



float vertices[] =
{	// positions       // colors		// texture coords
//	0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
//	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f, 0.0f, // bottom left
//	-0.5f, 0.5f, 0.0f, 0.0f , 0.0f, 0.0f, 0.0f, 1.0f, // top left  
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};




float texCoordSecond[] =
{
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
};

float texCoordSecond4s[] =
{
	4.0f, 4.0f,
	4.0f, 2.0f,
	2.0f, 2.0f,
	2.0f, 4.0f
};






float vertices2[] =
{
	0.0f, -0.5f, 0.0f, 1.0, 1.0 , 0.0, //second bottom
	-0.5f, 0.5f, 0.0f, 1.0, 1.0, 0.0,// top left
	-0.5f, -0.5f, 0.0f, 1.0 , 1.0 , 0.0 // bottom left
};

unsigned int indices[] =
{
	2, 3, 0,
	2, 1, 0, 
};


float textCoords1[] =
{
	0.0f, 0.0f, // bottom left corner
	1.0f, 0.0f, // bottom right corner
	1.0f, 1.0f, // top 
};







int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "hello", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to init glad" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);


	Shader ourShader1("main.vert", "main.frag");
	unsigned int VBO1, VBO2, VBO3;
	glGenBuffers(1, &VBO1);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &VBO3);
	unsigned int VAO1, VAO2, VAO3;
	glGenVertexArrays(1, &VAO1);
	glGenVertexArrays(1, &VAO2);
	glGenVertexArrays(1, &VAO3);
	// VAO - 0. bind vertex array object
	glBindVertexArray(VAO1);
	// VBO - 0. copy our vertices array in a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);







	// VBO - 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void*)(3*sizeof(float)));
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordSecond), texCoordSecond, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);


	Shader ourShader2("main2.vert", "main2.frag");

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	// CONTAINER TEXTURE
	unsigned int textures, textures2;
	glGenTextures(1, &textures);
	glBindTexture(GL_TEXTURE_2D, textures);	
	//set the texture wrapping/filtering options (on the currently bound object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else
	{
		std::cout << "failed to load texture: textures/container.jpg" << std::endl;
	}
	stbi_image_free(data);
	 
	// AWESOMEFACE TEXTURE
	glGenTextures(1, &textures2);
	glBindTexture(GL_TEXTURE_2D, textures2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "failed to load texture: textures/awesomeface.png" << std::endl;
	}
	stbi_image_free(data);
	// render loop
	float plusOpacity = 0.2f;
	while (!glfwWindowShouldClose(window))
	{

		//input
		processInput(window);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);




		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader1.use();
		//float currentOffset = sin(glfwGetTime()) * 0.5f;
		//ourShader1.setFloat("xOffSet", currentOffset);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			if (plusOpacity < 1)
			{
				plusOpacity += 0.005f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			if (plusOpacity > 0)
			{
				plusOpacity -= 0.005f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO3);
			glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordSecond4s), texCoordSecond4s, GL_STATIC_DRAW);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO3);
			glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordSecond), texCoordSecond, GL_STATIC_DRAW);
		}

		// gravity

		yVelocity -= gravity * deltaTime;

		cameraPos.y += (yVelocity * deltaTime);

		if (cameraPos.y < 0)
		{
			yVelocity = 0;
			cameraPos.y = 0;
		}


		//

		ourShader1.setFloat("opacity", plusOpacity);

		// right triangle
		// VBO - 2. use our shader program when we want to render an object
		glUseProgram(ourShader1.ID);
		// 3. now draw the object
		glUniform1i(glGetUniformLocation(ourShader1.ID, "ourTexture"),0);
		ourShader1.setInt("ourTexture2", 1);

		// creating matrixes and binding them with the vertex shader

		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		//glm::mat4 view = glm::mat4(1.0f);
		////note that we are translating the scene in the reverse direction of where we want to move
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

		//glm::mat4 projection;
		//projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		//int modelLoc = glGetUniformLocation(ourShader1.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//int viewLoc = glGetUniformLocation(ourShader1.ID, "view");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		//int projectionLoc = glGetUniformLocation(ourShader1.ID, "projection");
		//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//


		glActiveTexture(GL_TEXTURE0); //activate the texture unit first before binding texture
		glBindTexture(GL_TEXTURE_2D, textures);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures2);
		glBindVertexArray(VAO1);
		// second texture

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT , 0);
		glEnable(GL_DEPTH_TEST);		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

		
		glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

		ourShader1.setMat4("view", view);
		ourShader1.setMat4("projection", projection);


		for (unsigned int i = 0; i < 10; i++)
		{

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositiobs[i]);
			float angle = 20.0f * i;
			if (i%3 == 0)
			{
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
				ourShader1.setMat4("model", model);
			}
			else
			{
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				ourShader1.setMat4("model", model);
			}

			ourShader1.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}

		//glDrawArrays(GL_TRIANGLES, 0, 36);



		// left triangle
		ourShader2.use();
		glUseProgram(ourShader2.ID);
		glm::mat4 trans2 = glm::mat4(1.0f);
		trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
		//trans2 = glm::scale(trans2, glm::vec3((sin(glfwGetTime())/2) + 0.5f, 1.0f, 0.0f));
		//unsigned int transformLoc2 = glGetUniformLocation(ourShader2.ID, "transform2");
		//glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans2));

		//glBindVertexArray(VAO2);
		glBindVertexArray(0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);



		// ======================= // 

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	glm::vec3 flat = glm::vec3(cameraFront.x, 0.0f, cameraFront.z);



	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (cameraPos.y == 0)
		{
			yVelocity = 5.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cameraSpeed = 5.0f * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * glm::normalize(flat);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * glm::normalize(flat);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(flat, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(flat, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		fov = 45.0f;
	}


}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}




	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}



	glm::vec3 direction;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;

	if (fov < 1.0f)
	{
		fov = 1.0f;
	}
	if (fov > 45.0f)
	{
		fov = 45.0f;
	}
}


