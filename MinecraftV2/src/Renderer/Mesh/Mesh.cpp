#include "Mesh.h"
#include <iostream>

GLuint Mesh::getId()
{
	if (mVao == 0)
		glGenVertexArrays(1, &mVao);

	return mVao;
}

void Mesh::bindVao()
{
	glBindVertexArray(getId());
}

void Mesh::unbindVao()
{
	glBindVertexArray(0);
}

void Mesh::bufferMesh()
{
	release();

	bindVao();
	addVbo(3, vertices);
	addVbo(2, texCoords);
	addVbo(1, lights);
	addEbo(indices);
	unbindVao();

	vertices.clear();
	texCoords.clear();
	lights.clear();
	indices.clear();
	vertices.shrink_to_fit();
	texCoords.shrink_to_fit();
	lights.shrink_to_fit();
	indices.shrink_to_fit();
}

int Mesh::getIndicesCount() const
{
	return  mIndicesCount;
}

void Mesh::release()
{
	if (mVao)
	{
		glDeleteVertexArrays(1, &mVao);
		//std::cout << "[DEBUG/Model] Releasing VAO " << m_vao << ", prevented an internal memory leak!" << std::endl;
	}

	if (!mVboBuffers.empty())
		glDeleteBuffers(static_cast<GLsizei>(mVboBuffers.size()),
			mVboBuffers.data());

	// Feeling pretty stupid it took me 30 minutes to figure the part out below...
	mVboBuffers.clear();
	mVboBuffers.shrink_to_fit();

	mVboCount = 0;

	// Reset render info
	mVao = 0;
	mIndicesCount = 0;
}

void Mesh::addVbo(int dimensions, std::vector<GLfloat> buffer)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		buffer.size() * sizeof(GLfloat),
		buffer.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(static_cast<GLuint>(mVboCount),
		dimensions,
		GL_FLOAT,
		GL_FALSE,
		0,
		(GLvoid*)0);

	glEnableVertexAttribArray(static_cast<GLuint>(mVboCount++));

	mVboBuffers.push_back(vbo);
}

void Mesh::addEbo(std::vector<GLuint> buffer)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		buffer.size() * sizeof(GLuint),
		buffer.data(),
		GL_STATIC_DRAW);

	mIndicesCount = static_cast<GLuint>(buffer.size());

	//m_buffers.push_back(ebo);
}
