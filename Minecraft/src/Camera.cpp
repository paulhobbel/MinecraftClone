#define GLFW_INCLUDE_GLU
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);

	glTranslatef(position.x, position.y, position.z);
}
