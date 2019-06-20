#pragma once

#include "../../Entity.h"
#include "../../GameWindow.h"

class World;

class Player : public Entity
{
public:
	Player();

	void handleInput(GameWindow& window);
	void update(double deltaTime, World& world);
private:
	glm::vec3 mAcceleration;
};