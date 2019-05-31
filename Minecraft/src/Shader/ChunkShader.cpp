#include <glm/gtc/type_ptr.hpp>
#include "ChunkShader.h"

ChunkShader::ChunkShader() : Shader("Chunk", "Chunk")
{
}

void ChunkShader::LoadProjectionViewMatrix(const glm::mat4& matrix)
{
	glUniformMatrix4fv(m_projViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ChunkShader::GetUniforms()
{
	m_projViewMatrixLocation = glGetUniformLocation(m_id, "projViewMatrix");
}
