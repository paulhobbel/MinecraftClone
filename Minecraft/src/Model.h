#pragma once

#include <vector>
#include <glad/glad.h>

#include "Mesh.h"

struct RenderInfo
{
	GLuint vao = 0;
	GLuint indicesCount = 0;
};

class Model
{
public:
	Model() = default;
	~Model();

	void Create(const Mesh& mesh);
	void Release();

	void AddVBO(int dimensions, const std::vector<GLfloat>& data);

	void BindVAO();
	int GetIndicesCount() const;

	const RenderInfo& GetRenderInfo() const;

private:
	/*GLuint m_vao = 0;
	GLuint m_indicesCount = 0;*/
	RenderInfo m_renderInfo;

	int m_vboCount = 0;

	std::vector<GLuint> m_buffers;
};