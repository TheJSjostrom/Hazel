#include "Projectile.h"

void Projectile::OnUpdate(float ts)
{
	m_Position.x += cos(m_Angle) * m_VectorLength * (float)ts;
	m_Position.y += sin(m_Angle) * m_VectorLength * (float)ts;

	m_Distance += 0.2f;
	m_Rotation -= 5.0f;
}

void Projectile::OnRender()
{
	Hazel::Renderer2D::DrawQuad(m_Position, m_Size, m_Rotation, m_Color);
}

 