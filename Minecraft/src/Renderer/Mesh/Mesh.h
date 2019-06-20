#pragma once

#include <vector>
#include "glad/glad.h"

class Mesh
{
public:
	GLuint getId();

	void bindVao();
	void unbindVao();

	void bufferMesh();

	int getIndicesCount() const;

	virtual void release();

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texCoords;
	std::vector<GLfloat> lights;
	std::vector<GLuint> indices;

	// Tempfixxx
	GLuint mVao = 0;
private:
	
	int mVboCount = 0;
	GLuint mIndicesCount = 0;
	std::vector<GLuint> mVboBuffers;

	void addVbo(int dimensions, std::vector<GLfloat> buffer);
	void addEbo(std::vector<GLuint> buffer);
};
