#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct BlockPartFace
{
	std::string texture;
};

void from_json(const nlohmann::json& json, BlockPartFace& bpf);