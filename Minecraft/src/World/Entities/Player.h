#pragma once

#include "../../Entity.h"
#include "../../GameWindow.h"

class World;

class Player : public Entity
{
public:
	Player();

	void HandleInput(GameWindow* window);
	void Update(float deltaTime, World& world);
private:
	glm::vec3 m_acceleration;
};