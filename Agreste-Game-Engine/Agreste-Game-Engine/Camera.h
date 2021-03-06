#pragma once

// Std. Includes
#include <vector>

// GL Includes
//#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"CameraMovement.h"



// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVTY = 0.25f;
const GLfloat ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	void processGamePadAxisMovement(Camera_Movement direction, float axisValue, float deltaTime);


	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yOffset);

	GLfloat GetZoom();

	glm::vec3 GetPosition();
	
	glm::vec3 GetFront();

	void setPosition(glm::vec3 position);

	void setFront(glm::vec3 front);

	void setBehind(glm::vec3 position);

	GLfloat getYaw();

	GLfloat getPitch();

	void setYaw(GLfloat yaw);

	void setPitch(GLfloat pitch);

	GLfloat getMoveSpeed();

	void updateThirdPersonVectors();


protected:
	// Camera Attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	// Eular Angles
	GLfloat yaw;
	GLfloat pitch;


	// Camera options
	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();


	
	
};