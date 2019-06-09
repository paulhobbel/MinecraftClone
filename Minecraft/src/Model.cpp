#include "Model.h"
#include <iostream>

Model::~Model()
{
	Release();
}

void Model::Create(const Mesh& mesh)
{
	if (m_vao != 0)
		Release();

	// Generate and bind to vertex array (vao -> Vertex Array Object)
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	std::cout << "[DEBUG/Model] Generated VAO " << m_vao << std::endl;

	// Generate the vbos
	AddVBO(3, mesh.vertices);
	AddVBO(2, mesh.texCoords);

	m_indicesCount = static_cast<GLuint>(mesh.indices.size());

	// Generate the ebo
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		mesh.indices.size() * sizeof(GLuint),
		mesh.indices.data(),
		GL_STATIC_DRAW);

	m_buffers.push_back(ebo);

	//glBindVertexArray(0);
}

void Model::Release()
{
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
		std::cout << "[DEBUG/Model] Releasing VAO " << m_vao << std::endl;
	}

	if (m_buffers.size() > 0)
		glDeleteBuffers(static_cast<GLsizei>(m_buffers.size()),
			m_buffers.data());

	// Feeling pretty stupid it took me 30 minutes to figure the part out below...
	m_buffers.clear();

	m_vboCount = 0;

	// Reset render info
	m_vao = 0;
	m_indicesCount = 0;
}

void Model::BindVAO() const
{
	glBindVertexArray(m_vao);
}

const int Model::GetIndicesCount() const
{
	return m_indicesCount;
}

void Model::AddVBO(int dimensions, const std::vector<GLfloat>& data)
{
	// Generate vbo (vbo -> Vertex Buffer Object)
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		data.size() * sizeof(GLfloat),
		data.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(static_cast<GLuint>(m_vboCount),
		dimensions,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid*)0);

	glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount++));

	m_buffers.push_back(vbo);
}
