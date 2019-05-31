#define GLFW_INCLUDE_GLU
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>
#include "Camera.h"

void Camera::LoadProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, 1280.f / 720.f, 0.1f, 1000.f);
}

void Camera::LoadViewMatrix()
{
	glm::mat4 mat;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(position.x, position.y, position.z);

	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);

	
}
