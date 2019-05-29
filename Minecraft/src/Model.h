#pragma once

#include "Mesh.h"

class Model
{
public:
	Model() = default;
	Model(const Mesh& mesh);
	~Model();


};