#pragma once

#include <GLFW/glfw3.h>
#include <vector>

struct Mesh
{
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texCoords;
	std::vector<GLuint> indices;
};