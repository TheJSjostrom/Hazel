#pragma once
#include <glm/glm.hpp>
#include <Hazel.h>

class QuadPlayer 
{
public:
	void OnUpdate(Hazel::Timestep ts);
	void OnRender();

	void OnImGuiRender();

	void Reset();

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec2& GetSize() const { return m_Size; }
	float GetRotation() const { return m_Rotation; }

private:
	glm::vec3 m_Position = { -6.0f, -6.0f, 0.0f };
	glm::vec2 m_Size = { 0.5f, 0.5f };
	glm::vec4 m_Color = { 1.0f, 1.0f, 0.0f, 1.0f };

	float m_Rotation = 45.0f;
	float m_Velocity = 6.0f; 
	
};