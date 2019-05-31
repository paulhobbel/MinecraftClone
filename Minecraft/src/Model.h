#pragma once

#include <array>
#include <glad/glad.h>

#include "Mesh.h"

class Model
{
public:
	Model() = default;
	Model(const Mesh& mesh);
	~Model();

	void AddData(const Mesh& mesh);
	void DeleteData();

	void BindVAO();
	int GetIndicesCount();

private:
	GLuint m_vao = 0;
	GLuint m_indicesCount = 0;

	int m_vboCount = 0;

	void AddVBO(int dimensions, const std::vector<GLfloat>& data);

	std::vector<GLuint> m_buffers;
};