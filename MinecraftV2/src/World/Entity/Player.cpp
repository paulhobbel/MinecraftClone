#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Player.h"
#include "../../Input/Keyboard.h"
#include "../../Input/Mouse.h"

#include "../World.h"

Player::Player() : Entity({ 2500, 125, 2500 }, { 0.f, 0.f, 0.f }, { 0.3f, 1.f, 0.3f })
{
}

void Player::handleInput(GameWindow& window)
{
	if (Keyboard::isPressed(GLFW_KEY_W))
	{
		float speed = .2f;
		if (Keyboard::isPressed(GLFW_KEY_LEFT_CONTROL))
		{
			speed *= 3;
		}
		mAcceleration.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
		mAcceleration.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
	}

	if (Keyboard::isPressed(GLFW_KEY_S))
	{
		mAcceleration.x += glm::cos(glm::radians(rotation.y + 90)) * .2f;
		mAcceleration.z += glm::sin(glm::radians(rotation.y + 90)) * .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_A))
	{
		mAcceleration.x += -glm::cos(glm::radians(rotation.y)) * .2f;
		mAcceleration.z += -glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_D))
	{
		mAcceleration.x += glm::cos(glm::radians(rotation.y)) * .2f;
		mAcceleration.z += glm::sin(glm::radians(rotation.y)) * .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_SPACE))
	{
		jump();
		//mAcceleration.y += .2f;
	}

	if (Keyboard::isPressed(GLFW_KEY_LEFT_SHIFT))
	{
		mAcceleration.y -= .2f;
	}

	static auto lastMousePosition = Mouse::getPosition(&window);

	if (window.hasFocus())
	{
		auto deltaPos = Mouse::getPosition(&window) - lastMousePosition;

		rotation.y += deltaPos.x * 0.05;
		rotation.x += deltaPos.y * 0.05;

		if (rotation.x > 90.f) rotation.x = 90.f;
		else if (rotation.x < -90.f) rotation.x = -90.f;

		if (rotation.y > 360) rotation.y = 0;
		else if (rotation.y < 0) rotation.y = 360;

		//std::cout << "Rotation: " << glm::to_string(rotation) << ", deltaPos: " << glm::to_string(deltaPos) << std::endl;

		auto cx = static_cast<int>(window.getSize().x / 2);
		auto cy = static_cast<int>(window.getSize().y / 2);

		Mouse::setPosition({ cx, cy }, &window);

		lastMousePosition = Mouse::getPosition(&window);
	}
}

void Player::update(double deltaTime, World& world)
{
	velocity += mAcceleration;
	mAcceleration = { 0, 0, 0 };

	if (!mFlying)
	{
		if (!mOnGround)
		{
			velocity.y -= 40 * deltaTime;
		}
		mOnGround = false;
	}

	if (position.y <= 0 && !mFlying) {
		position.y = 300;
	}

	position.x += velocity.x * deltaTime;
	collide(world, { velocity.x, 0, 0 }, deltaTime);

	position.y += velocity.y * deltaTime;
	collide(world, { 0, velocity.y, 0 }, deltaTime);

	position.z += velocity.z * deltaTime;
	collide(world, { 0, 0, velocity.z }, deltaTime);

	boundingBox.update(position);

	velocity.x *= 0.95f;
	velocity.y *= 0.95f;
	velocity.z *= 0.95f;
}

void Player::collide(World& world, const glm::vec3& vel, double dt)
{
	for (int x = position.x - boundingBox.dimensions.x; x < position.x + boundingBox.dimensions.x; x++)
		for (int y = position.y - boundingBox.dimensions.y; y < position.y + 0.7; y++)
			for (int z = position.z - boundingBox.dimensions.z; z < position.z + boundingBox.dimensions.z; z++)
			{
				auto block = world.getBlock(x, y, z);

				if (block != BlockId::Air)
				{
					if (vel.y > 0)
					{
						position.y = y - boundingBox.dimensions.y;
						velocity.y = 0;
					}
					else if (vel.y < 0)
					{
						mOnGround = true;
						position.y = y + boundingBox.dimensions.y + 1;
						velocity.y = 0;
					}

					if (vel.x > 0)
					{
						position.x = x - boundingBox.dimensions.x;
					}
					else if (vel.x < 0)
					{
						position.x = x + boundingBox.dimensions.x + 1;
					}

					if (vel.z > 0)
					{
						position.z = z - boundingBox.dimensions.z;
					}
					else if (vel.z < 0)
					{
						position.z = z + boundingBox.dimensions.z + 1;
					}
				}
			}
}

void Player::jump()
{
	if (!mFlying)
	{
		if (mOnGround)
		{
			mOnGround = false;
			mAcceleration.y += .2f * 50;
		}
	}
	else
	{
		mAcceleration.y += .2f * 3;
	}
}