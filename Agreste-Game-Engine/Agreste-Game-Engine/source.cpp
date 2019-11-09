#include<iostream>
//GLEW
#include<GL/glew.h>
//GLFW
#include<GLFW/glfw3.h>
//SOIL2
#include<SOIL2/SOIL2.h>

#include"Shader.h"

//Window dimensions
const GLint WIDHT = 800, HEIGHT = 600;


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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("core.vs","core.fs");

	// Set up vertex data (and buffer(s)) and attribute pointers

	GLfloat vertices[] =
	{	//position							//color								//Texture Coordinates
		0.5f, 0.5f, 0.0f,						1.0f, 0.0f, 0.0f,						1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,						0.0f, 1.0f, 0.0f,						1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,						0.0f, 0.0f, 1.0f,						0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,						1.0f,1.0f,0.0f,							0.0f, 1.0f
	};

	GLuint indices[] =
	{
		0,1,3, //first triangle
		1,2,3 //second triangle

	};

	GLuint VAO, VBO, EBO;
	glGenBuffers(1,&EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind vertex array object fisrt
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	//texture coordinate attribute 
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	//

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	GLuint texture;

	int width, height;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *image = SOIL_load_image("images/som.png", &width, &height, 0, SOIL_LOAD_RGBA  );
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);



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

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture"), 0);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers

		glfwSwapBuffers(window);
	}



	// Properly de-allocate all resources once they've outlived their purpose

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.

	glfwTerminate();

	return EXIT_SUCCESS;

}
