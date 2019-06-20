#pragma once
#include "IWorldEvent.h"
#include <glm/vec3.hpp>

class Player;

class PlayerDigEvent : public IWorldEvent
{
public:
	PlayerDigEvent(Player& player, const glm::vec3& location);
	void handle(World& world) override;
private:
	void dig(World& world);

	Player* mPlayer;
	glm::vec3 mDigPosition;
};
