#pragma once

class GLResource
{
public:
	virtual ~GLResource() = default;
	virtual void dispose() = 0;
};