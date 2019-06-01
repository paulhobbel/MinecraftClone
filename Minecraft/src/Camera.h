#pragma once

#include <glm/matrix.hpp>
#include "Entity.h"

class GameWindow;

class Camera : public Entity
{
public:
	Camera();

	void SetPerspective(glm::vec2 windowSize) noexcept;
	void Update(GameWindow* window) noexcept;

	glm::mat4& getProjectionMatrix();
	glm::mat4& getViewMatrix();
	glm::mat4& getProjectionViewMatrix();
private:
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrix;
};

