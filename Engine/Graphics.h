#pragma once
#include <glm/glm.hpp>

class Graphics
{
public:
	Graphics();
	~Graphics();

	void CreateWindow(const char* title, int width, int height, float size = 8);
	void Clear();
	void Present();
	inline void SetColor(const glm::vec4& color);

	void Drawpoint(const glm::ivec2& point, const glm::vec4 color);
	void DrawLine(const glm::ivec2& start, const glm::ivec2& end, glm::vec4 color);
	void DrawCircle(const glm::ivec2& point, const float radius, const glm::vec4 color);
	void DrawFilledCircle(const glm::ivec2& point, const float radius, const glm::vec4 color);

	glm::vec2 ScreenToWorld(const glm::ivec2& screen);
	glm::ivec2 WorldToScreen(const glm::vec2& world);
	int WorldToPixels(float world);

	const glm::vec2& GetWorldExtents() const { return m_extents; }

	glm::ivec4 ConvertColor(glm::vec4& color);

private:
	int m_width{ 0 };
	int m_height{ 0 };
	glm::vec2 m_extents{ 0 };

	struct SDL_Window* m_window{ nullptr };
	struct SDL_Renderer* m_renderer{ nullptr };
};
