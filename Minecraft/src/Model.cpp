#include "Model.h"
#include <iostream>

Model::~Model()
{
	Release();
}

void Model::Create(const Mesh& mesh)
{
	if (mesh.indices.size() == 0 && mesh.vertices.size() == 0)
	{
		std::cout << "[WARN/Model] Leak detected! Tried to create empty VAO. Unexpected things can happen now!" << std::endl;
		return;
	}

	if (m_renderInfo.vao != 0)
		Release();

	// Generate and bind to vertex array (vao -> Vertex Array Object)
	glGenVertexArrays(1, &m_renderInfo.vao);
	glBindVertexArray(m_renderInfo.vao);

	//std::cout << "[DEBUG/Model] Generated VAO " << m_renderInfo.vao << std::endl;

	// Generate the vbos
	AddVBO(3, mesh.vertices);
	AddVBO(2, mesh.texCoords);

	m_renderInfo.indicesCount = static_cast<GLuint>(mesh.indices.size());

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
	if (m_renderInfo.vao)
	{
		glDeleteVertexArrays(1, &m_renderInfo.vao);
		std::cout << "[WARN/Model] Releasing VAO " << m_renderInfo.vao << std::endl;
	}

	if (m_buffers.size() > 0)
		glDeleteBuffers(static_cast<GLsizei>(m_buffers.size()),
			m_buffers.data());

	// Feeling pretty stupid it took me 30 minutes to figure the part out below...
	m_buffers.clear();

	m_vboCount = 0;

	// Reset render info
	m_renderInfo.vao = 0;
	m_renderInfo.indicesCount = 0;
}

void Model::BindVAO()
{
	glBindVertexArray(m_renderInfo.vao);
}

const RenderInfo& Model::GetRenderInfo() const
{
	return m_renderInfo;
}

int Model::GetIndicesCount() const
{
	return m_renderInfo.indicesCount;
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
