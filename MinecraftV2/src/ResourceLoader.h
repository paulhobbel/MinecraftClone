#pragma once

#include <map>

class ModelBlock;

class ResourceLoader
{
	friend class ModelBlock;
public:
	void loadBlocks();

private:
	std::map<std::string, ModelBlock> mBlocks;
};
