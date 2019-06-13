#include "BlockPartFace.h"

void from_json(const nlohmann::json& json, BlockPartFace& bpf)
{
	bpf.texture = json.at("texture").get<std::string>();
}
