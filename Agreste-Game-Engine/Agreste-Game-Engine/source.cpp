#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#include "SOIL2/SOIL2.h"
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "GameObject.h"
#include "GameBoard.h"
#include "Physics.h"

#define threshold  0.5

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void joystick_callback(int jid, int event);
//void DoMovement();
void joyPadTest(bool test);
void movePlayer(GameBoard board);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;


// Camera
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
int count1;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "AGE", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetJoystickCallback(joystick_callback);

		
	
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	GameBoard board(SCREEN_WIDTH, SCREEN_HEIGHT);
	board.addGameObject("../Agreste-Game-Engine/images/cube.obj");
	(*board.gameObjects[0]).setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	(*board.gameObjects[0]).setRawColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
	(*board.gameObjects[0]).unfix();
	board.addGameObject("../Agreste-Game-Engine/platform.obj");
	(*board.gameObjects[1]).setPosition(glm::vec3(0.0f, 2.0f, -15.0f));
	(*board.gameObjects[1]).setStencilMode(true);
	board.addGameObject("../Agreste-Game-Engine/platform.obj");
	(*board.gameObjects[2]).setPosition(glm::vec3(0.0f, 4.0f, -20.0f));
	(*board.gameObjects[2]).setStencilMode(true);
	board.addGameObject("../Agreste-Game-Engine/platform.obj");
	(*board.gameObjects[3]).setPosition(glm::vec3(0.0f, 6.0f, -25.0f));
	(*board.gameObjects[3]).setStencilMode(true);

	

	GameObject * Player = board.gameObjects[0];
	Camera * cam = board.getCamera();
	(*cam).setBehind((*Player).getPosition());
	Physics py;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//movementBox = glm::vec3(0);
		//float y = (*Player).getPosition().y + 5;
		//glm::vec3 camPos((*cam).GetPosition().x, y, (*cam).GetPosition().z);

		//(*board.getCamera()).setPosition(camPos);

		py.gravityForce(board.gameObjects, deltaTime);
		board.thirdPersonCamera((*board.gameObjects[0]));
		board.drawGameObjects();//se n�o tiver game objects ele desenha o skybox sozinho

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		movePlayer(board);
		
		if ((*Player).getPosition().y < 4.0f)
		{
			(*Player).setStencilMode(false);
			if (py.detectCollision(*Player, (*board.gameObjects[1])))
			{
				(*Player).Move(py.normalResponse, deltaTime);
			}
		}
		else if ((*Player).getPosition().y > 4 && (*Player).getPosition().y < 6.0f)
		{
			(*Player).setStencilMode(false);
			if (py.detectCollision(*Player, (*board.gameObjects[2])))
			{
				(*Player).Move(py.normalResponse, deltaTime);
			}
		}
		else
		{
			if (py.detectCollision(*Player, (*board.gameObjects[3])))
			{
				(*Player).Move(py.normalResponse, deltaTime);
				(*Player).setStencilMode(true);
			}
		}

		
		//(*board.gameObjects[0]).setPosition((*board.gameObjects[0]).getPosition() + movementBox);
		//DoMovement();
		joyPadTest(false);
	
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

	

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
/*void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}*/

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	//camera.ProcessMouseMovement(xOffset, yOffset);
}

void joyPadTest(bool test) 
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (1==present)
	{
		int axisCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);
		int buttonCount;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		if (test == true)
		{
			cout << "Left Stick X Axis:" << axes[0] << endl;
			cout << "Left Stick Y Axis:" << axes[1] << endl;
			cout << "Right Stick X Axis:" << axes[2] << endl;
			cout << "Right Stick Y Axis:" << axes[3] << endl;
			cout << "Left Trigger Axis:" << axes[4] << endl;
			cout << "Right Trigger Axis:" << axes[5] << endl;

			if (GLFW_PRESS == buttons[0])
			{
				cout << "A Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[1])
			{
				cout << "B Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[2])
			{
				cout << "X Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[3])
			{
				cout << "Y Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[4])
			{
				cout << "LB Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[5])
			{
				cout << "RB Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[6])
			{
				cout << "Select Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[7])
			{
				cout << "Start Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[8])
			{
				cout << "Left Analog Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[9])
			{
				cout << "Right Analog Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[10])
			{
				cout << "Directional Up Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[11])
			{
				cout << "Directional Right Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[12])
			{
				cout << "Directional Down Button pressed" << endl;
			}
			else if (GLFW_PRESS == buttons[13])
			{
				cout << "Directional Left Button pressed" << endl;
			}
			system("CLS");
		}
	}
	
}

void movePlayer(GameBoard board)
{
	GameObject * p1 = board.gameObjects[0];
	Camera *cam = board.getCamera();
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	if (1 == present)
	{
		int axisCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axisCount);

		if (axes[1] > threshold || axes[1] < -threshold) {//front x back
			p1->processGamePadAxisMovement(FORWARD, axes[1], deltaTime);
			(*board.getCamera()).processGamePadAxisMovement(FORWARD, axes[1], deltaTime);
		}
												  
		if(axes[0] > threshold || axes[0] < -threshold) //left x right
			p1->processGamePadAxisMovement(RIGHT, axes[0], deltaTime);
			
		if (axes[2] > threshold || axes[2] < -threshold || axes[3]>threshold || axes[3] < -threshold) 
		{ //camera
		//camera.ProcessMouseMovement(0.3*axes[2], -0.3*axes[3]);
			(*p1).processGamePadAxisRotation(0.3*axes[2], -0.3*axes[3]);
			//cout << (*p1).getYaw() << endl;
			//cout << "front-> (" << (*p1).getFront().x << "," << (*p1).getFront().y << "," << (*p1).getFront().z << ")" << endl;

		}
		int buttonCount;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		if (GLFW_PRESS == buttons[0])
		{
			glm::vec3 direction = (*p1).getUp();
			direction *= 5;
			(*p1).Move(direction, deltaTime*5);
			float y = (*p1).getPosition().y + 6.5f;
			glm::vec3 camPos((*cam).GetPosition().x, y, (*cam).GetPosition().z);
			(*cam).setPosition(camPos);
			cout << "(" << (*p1).getPosition().x << ", " << (*p1).getPosition().y << ", " << (*p1).getPosition().z << ")" << endl;
			
			
			/*cout << "--------------posicao -------------" << endl;
			cout << "(" << (*p1).getPosition().x << ", " << (*p1).getPosition().y << ", " << (*p1).getPosition().z << ")" << endl;
			cout << "--------------posicao -------------" << endl;
			cout << "(" << camera.GetPosition().x << ", " << camera.GetPosition().y << ", " << camera.GetPosition().z << ")" << endl;
			cout << "--------------posicao -------------" << endl;
			for (size_t i = 0; i < (*p1).getModel().meshes[0].vertices.size(); i++)
			{
				glm::vec3 pos = (*p1).getModel().meshes[0].vertices[i].Position + (*p1).getPosition();
				cout << "(" << pos.x <<","<< pos.y <<","<< pos.z <<")"<< endl;
				camera.setBehind((*p1).getPosition(), (*p1).getFront());
				cout << "-----Comprimento=" << (*p1).getModel().meshes[0].length << "//altura=" << (*p1).getModel().meshes[0].height << "//largura" << (*p1).getModel().meshes[0].width << "-----" <<endl;
			}
			cout << "--------------fim -------------"<< endl;*/
		}
		

	}
}

void joystick_callback(int jid, int event)
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
	const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
	if (event == GLFW_CONNECTED)
	{
		cout << name << " conectado " << present;
	}
	else if (event == GLFW_DISCONNECTED)
	{
		cout  << " desconactado " << present;
	}
}
