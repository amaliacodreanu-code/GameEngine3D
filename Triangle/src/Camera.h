#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>

#include "ShaderClass.h"

class Camera
{
    public:
    glm::vec3 cameraPos;
    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);
     
    int width;
    int height; 

    bool firstClick = true;
        
    float speed  = 0.001f;
    float sensitivity = 100.0f;

    // Camera constructor to set up initial values
    Camera(int width, int height, glm::vec3 position);
   
    // Updates the camera matrix to the Vertex Shader
	 void updateMatrix(float fieldOfView, float nearPlane, float farPlane);

    // Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);

	// Handles camera inputs
	void Inputs(GLFWwindow* window);

};
 #endif // CAMERA_CLASS_H






