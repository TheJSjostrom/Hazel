#include "QuadPlayer.h"

using namespace Hazel;


void QuadPlayer::OnUpdate(Hazel::Timestep ts)
{
	if (Input::IsKeyPressed(HZ_KEY_A))
	{
		m_Rotation += m_Velocity * (float)ts;
	} 
	else if (Input::IsKeyPressed(HZ_KEY_D))
	{
		m_Rotation -= m_Velocity * (float)ts;
	}

	if (Input::IsKeyPressed(HZ_KEY_LEFT_SHIFT)) 
	{ 
		m_Velocity = 5.0f * 1.5f;
	}
	else if (!Input::IsKeyPressed(HZ_KEY_LEFT_SHIFT))
	{
		m_Velocity = 5.0f;
	}

	if (m_Position.x <= -9.7f)
	{
		m_Position.x = -9.7f;
	} 
	else if (m_Position.x >= 9.7f)
	{
		m_Position.x = 9.7f;
	}

	if (m_Position.y <= -9.7f)
	{
		m_Position.y = -9.7f;
	}
	else if (m_Position.y >= 9.7f)
	{
		m_Position.y = 9.7f;
	}

	if (Input::IsKeyPressed(HZ_KEY_W))
	{
		m_Position.x += cos(m_Rotation) * m_Velocity * (float)ts;
		m_Position.y += sin(m_Rotation) * m_Velocity * (float)ts;
	}

	if (Input::IsKeyPressed(HZ_KEY_S))
	{
		m_Position.x -= cos(m_Rotation) * m_Velocity * (float)ts;
		m_Position.y -= sin(m_Rotation) * m_Velocity * (float)ts;
	}
 
}

void QuadPlayer::OnRender()
{
	Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, m_Size, m_Rotation, m_Color);
}

void QuadPlayer::OnImGuiRender()
{
	
}

void QuadPlayer::Reset()
{
	m_Position = { -6.0f, -6.0f, 0.0f };
	m_Rotation = 45.0f;
}

