#pragma once

#include <string>
#include <glad/glad.h>
#include "BaseTexture.h"

class SimpleTexture : public BaseTexture
{
public:
	SimpleTexture() = default;
	void loadFromFileS(const std::string& file);
};
