#pragma once

#include "Entity.h"

class Camera : public Entity
{
public:
	void Update() noexcept;

	void LoadProjectionMatrix();
	void LoadViewMatrix();
};

