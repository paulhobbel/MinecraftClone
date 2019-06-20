#pragma once

#include <glad/glad.h>
#include "../GLResource.h"

class BaseTexture : public GLResource
{
public:
	virtual ~BaseTexture();

	GLuint getId();

	virtual void upload();

	void bind() const;

	void dispose() override;
protected:
	GLuint mId = 0;
};
