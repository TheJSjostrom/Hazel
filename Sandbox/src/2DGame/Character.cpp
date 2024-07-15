#include "Character.h"

using namespace Hazel;


void Character::OnUpdate(Hazel::Timestep ts)
{

	if (Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL)) 
	{ 
		m_Velocity = 10.0f;
	}
	else if (!Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL))
	{
		m_Velocity = 5.0f;
	}

	if (Input::IsKeyPressed(HZ_KEY_A) || Input::IsKeyPressed(HZ_KEY_LEFT))
	{
		m_Position.x -= m_Velocity * (float)ts;

		if (m_Position.x < -9.5f)
		{
			m_Position.x += m_Velocity * (float)ts;
		}
	}
	if (Input::IsKeyPressed(HZ_KEY_D) || Input::IsKeyPressed(HZ_KEY_RIGHT))
	{
		m_Position.x += m_Velocity * (float)ts;


		if (m_Position.x > 9.5f)
		{
			m_Position.x -= m_Velocity * (float)ts;
		}
	}
	if (Input::IsKeyPressed(HZ_KEY_W) || Input::IsKeyPressed(HZ_KEY_UP))
	{
		m_Position.y += m_Velocity * (float)ts;

		if (m_Position.y > 9.4f)
		{
			m_Position.y -= m_Velocity * (float)ts;
		}
	}
	if (Input::IsKeyPressed(HZ_KEY_S) || Input::IsKeyPressed(HZ_KEY_DOWN))
	{
		m_Position.y -= m_Velocity * (float)ts;

		if (m_Position.y < -9.4f)
		{
			m_Position.y += m_Velocity * (float)ts;
		}
	}
}

void Character::OnRender()
{
	Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, { 1.0f, 1.3f }, 0.0f, {1.0f, 1.0f, 0.0f, 1.0f});
}

void Character::OnImGuiRender()
{
	
}

