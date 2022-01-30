#ifndef CAMERA_CALSS_H
#define CAMERA_CALSS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../Shaders/ShaderClass.h"


class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); //Direction of camera
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f); //Up direction of camera
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	bool firstClick = true;
	
	int width;
	int height;

	float speed = 1.0f;//speed of camera
	float senesitivity = 100.0f;//sensetivity of camera

	Camera(int width, int height, glm::vec3 position);//init func
	
	/*
	* Send view and projection matracies to shader
	*/
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);

	// camera inputs
	void Inputs(GLFWwindow* window);






};





#endif // !CAMERA_CALSS_H

