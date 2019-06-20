#pragma once

#include <glm/matrix.hpp>
#include "Entity.h"
#include "ViewFrustum.h"

class GameWindow;

class Camera : public Entity
{
public:
	Camera();

	void bindEntity(const Entity& entity) noexcept;
	void setPerspective(glm::vec2 windowSize) noexcept;
	void update() noexcept;

	glm::mat4& getProjectionMatrix();
	glm::mat4& getViewMatrix();
	const glm::mat4& getProjectionViewMatrix() const;

	const ViewFrustum& getFrustum() const noexcept;
private:
	const Entity* mEntity;
	ViewFrustum mFrustum;

	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;
	glm::mat4 mProjViewMatrix;
};

