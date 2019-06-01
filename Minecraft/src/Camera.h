#pragma once

#include <glm/matrix.hpp>
#include "Entity.h"

class GameWindow;

class Camera : public Entity
{
public:
	Camera();

	void BindEntity(const Entity& entity) noexcept;
	void SetPerspective(glm::vec2 windowSize) noexcept;
	void Update() noexcept;

	glm::mat4& getProjectionMatrix();
	glm::mat4& getViewMatrix();
	glm::mat4& getProjectionViewMatrix();
private:
	const Entity* m_entity;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrix;
};

