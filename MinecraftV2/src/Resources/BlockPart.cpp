#include "BlockPart.h"

void from_json(const nlohmann::json& json, BlockPart& bp)
{
	bp.faces = json.at("faces").get<std::map<std::string, BlockPartFace>>();
}
