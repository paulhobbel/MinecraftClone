#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include "../World/Chunk/ChunkMesh.h"
#include "ChunkRenderer.h"
#include "../Camera.h"

namespace
{
	const std::array<GLfloat, 12> frontFace
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1
	};

	const std::array<GLfloat, 12> backFace
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0
	};

	const std::array<GLfloat, 12> leftFace
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0
	};

	const std::array<GLfloat, 12> rightFace
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};

	const std::array<GLfloat, 12> topFace
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0
	};

	const std::array<GLfloat, 12> bottomFace
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};
}

ChunkRenderer::ChunkRenderer()
{
	ChunkMesh mesh;
	

	mesh.AddFace(frontFace, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 });

	m_chunks.push_back(mesh);
}

void ChunkRenderer::Add(const ChunkMesh& mesh)
{
	m_chunks.push_back(mesh);
}

void ChunkRenderer::Render(Camera& camera)
{
	camera.LoadProjectionMatrix();

	if (m_chunks.empty())
	{
		return;
	}

	camera.LoadViewMatrix();

	//glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glColor3f(0, 0, 0);

	// Front
	/*glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);

	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glEnd();*/

	// Back
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glEnd();

	glEnableClientState(GL_VERTEX_ARRAY);
	// Bind textures

	for (auto& mesh : m_chunks)
	{
		camera.LoadViewMatrix();

		glVertexPointer(3, GL_FLOAT, mesh.GetMesh().vertices.size() * sizeof(std::vector<GLfloat>), mesh.GetMesh().vertices.data());

		glDrawArrays(GL_TRIANGLES, 0, mesh.GetMesh().vertices.size());

		// Render mesh
	}

	glDisableClientState(GL_VERTEX_ARRAY);

	//m_chunks.clear();
}
