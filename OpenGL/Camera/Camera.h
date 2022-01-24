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

	bool firstClick = true;
	
	int width;
	int height;

	float speed = 1.0f;//speed of camera
	float senesitivity = 100.0f;//sensetivity of camera

	Camera(int width, int height, glm::vec3 position);//init func
	
	/*
	* Send view and projection matracies to shader
	*/
	void Matrix(float FOVdeg, float nearplane, float farplane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);






};





#endif // !CAMERA_CALSS_H

