#pragma once
#include "Hazel.h"

class Projectile
{
public:
	void OnUpdate(float ts);
	void OnRender();

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	const glm::vec3& GetPosition() const { return m_Position; }

	void SetAngle(float rotation) { m_Angle = rotation; }

	float GetRotation() const { return m_Rotation; }

	float GetDistance() const { return m_Distance; }

	const glm::vec3& GetSize() const { return m_Size; }

private:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Size = { 0.3f, 0.3f, 1.0f };
	glm::vec4 m_Color = { 0.877f, 0.595f, 0.138f, 1.0f };

	float m_Distance = 0.0f;
	float m_Rotation = 0.0f;
	float m_VectorLength = 12.0f;
	float m_Angle = 0.0f;
};