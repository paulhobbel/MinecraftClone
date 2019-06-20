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
	void collide(World& world, const glm::vec3& vel, double dt);
	void jump();
private:
	bool mFlying = false;
	bool mOnGround = false;
	glm::vec3 mAcceleration;
};