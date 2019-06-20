#include <glm/gtc/type_ptr.hpp>
#include "ChunkShader.h"

ChunkShader::ChunkShader() : Shader("Chunk", "Chunk")
{
}

void ChunkShader::loadProjectionViewMatrix(const glm::mat4& matrix)
{
	glUniformMatrix4fv(m_projViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ChunkShader::getUniforms()
{
	useProgram();
	m_projViewMatrixLocation = glGetUniformLocation(m_id, "projViewMatrix");
}
