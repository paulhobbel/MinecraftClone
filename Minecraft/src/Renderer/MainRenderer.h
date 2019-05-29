#pragma once

class ChunkRenderer;

class MainRenderer
{
public:
	void PreRender();
	void Render();
	void PostRender();

private:
	ChunkRenderer m_chunkRenderer;
};

