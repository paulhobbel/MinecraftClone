#pragma once

#include <map>
#include <string>

#include "ModelBlock.h"

class ModelProvider
{
public:
	ModelBlock LoadBlock(std::string location);

private:
	std::map<std::string, ModelBlock> m_blocks;
};