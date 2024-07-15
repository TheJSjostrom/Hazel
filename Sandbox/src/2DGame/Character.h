#pragma once
#include <glm/glm.hpp>
#include <Hazel.h>

class Character
{
public:
	void OnUpdate(Hazel::Timestep ts);
	void OnRender();

	void OnImGuiRender();

private:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	float m_Velocity = 5.0f;
};