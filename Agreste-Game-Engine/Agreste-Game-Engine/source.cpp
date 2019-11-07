#include<iostream>
//GLEW
#include<GL/glew.h>
//GLFW
#include<GLFW/glfw3.h>
#include"Shader.h"

//Window dimensions
const GLint WIDHT = 800, HEIGHT = 600;

// Shaders





//the main function, game loop is inside

int main() 
{
	//init GLFW
	glfwInit();

	//set the requirement options for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create a new GLFW window
	GLFWwindow *window = glfwCreateWindow(WIDHT, HEIGHT, "Agreste Game Engine",nullptr, nullptr );

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr==window) 
	{
		std::cout << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	//use this, so GLEW know to use the modern functions
	glewExperimental = GL_TRUE;

	//initialize GLEW to setup the OpenGL Funcion Pointers
	if (GLEW_OK!=glewInit()) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	//define viewport dimensions
	glViewport(0,0, screenWidth, screenHeight);

	Shader ourShader("core.vs","core.fs");

	// Set up vertex data (and buffer(s)) and attribute pointers

	GLfloat vertices[] =
	{	//position							//color
		-0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,// Left  red
		0.5f, -0.5f, 0.0f,			0.0f, 0.0f, 1.0f,// Right blue
		0.0f,  0.5f, 0.0f,			0.0f, 1.0f, 0.0f // Top green
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our first triangle

		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap the screen buffers

		glfwSwapBuffers(window);
	}



	// Properly de-allocate all resources once they've outlived their purpose

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.

	glfwTerminate();

	return EXIT_SUCCESS;

}
