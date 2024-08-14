#pragma once
#include <glm/glm.hpp>
#include <Hazel.h>

class TrianglePlayer
{
public:
	void OnUpdate(Hazel::Timestep ts);
	void OnRender();

	void OnImGuiRender();
	void LoadAssets();
	void Reset();

	glm::vec3& GetPosition() { return m_Position; }
	const glm::vec2& GetSize() { return m_Size; }
	float GetRotation() { return m_Rotation; }
private:
	Hazel::Ref<Hazel::Texture2D> m_TriangleTexture;
	glm::vec3 m_Position = { 6.0f, 6.0f, 0.0f };
	glm::vec2 m_Size = { 1.25f, 1.25f };

	float m_Rotation = 59.7f;
	float m_Velocity = 2.0f;
};