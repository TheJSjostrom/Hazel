#pragma once
#include "Hazel.h"

class PlayerQuad1
{
public:
	void OnUpdate(Hazel::Timestep ts, int TriangleLife);
	void OnRender();

	const glm::vec3& GetPosition() const { return m_Position; }
	const glm::vec3& GetSize() const { return m_Size; }
	glm::vec4& GetColor() { return m_Color; }
	const float GetRotation() const { return m_Rotation; }
	
	void SetProjectileCount(int ProjectileCount) { m_ProjectileCount = ProjectileCount; }
	void SetCollisionTest(bool CollisionTest) { m_CollisionTest = CollisionTest; }

private:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::vec4 m_Color = { 0.5f, 1.0f, 1.0f, 1.0f };
	glm::vec3 m_Size = { 0.75f, 0.75f, 1.0f };

	int m_ProjectileCount = 50;
	float m_Velocity = 2.0f;
	float m_Rotation = 0.0f;
	bool m_CollisionTest = false;
};