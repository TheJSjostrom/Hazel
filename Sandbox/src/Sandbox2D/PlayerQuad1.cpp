#include "PlayerQuad1.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Events/MouseEvent.h"
#include "glm/glm/trigonometric.hpp"

using namespace Hazel;

void PlayerQuad1::OnUpdate(Hazel::Timestep ts, int TriangleLife)
{

	if (Input::IsKeyPressed(HZ_KEY_Z))
	{
		m_Rotation += 6.0f * (float)ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_X))
	{
		m_Rotation -= 6.0f * (float)ts;
	}

	if (Input::IsKeyPressed(HZ_KEY_A))
	{
		m_Position.x -= m_Velocity * (float)ts;

		if (TriangleLife > 0)
		{
			if (m_CollisionTest)
			{
				m_Position.x += m_Velocity * (float)ts;
			}
		}
	}
	else if (Input::IsKeyPressed(HZ_KEY_D))
	{
		m_Position.x += m_Velocity * (float)ts;

		if (TriangleLife > 0)
		{
			if (m_CollisionTest)
			{
				m_Position.x -= m_Velocity * (float)ts;
			}
		}
	}

	if (Input::IsKeyPressed(HZ_KEY_W))
	{
		m_Position.y += m_Velocity * (float)ts;

		if (TriangleLife > 0)
		{
			if (m_CollisionTest)
			{
				m_Position.y -= m_Velocity * (float)ts;
			}
		}
	}
	else if (Input::IsKeyPressed(HZ_KEY_S))
	{
		m_Position.y -= m_Velocity * (float)ts;

		if (TriangleLife > 0)
		{
			if (m_CollisionTest)
			{
				m_Position.y += m_Velocity * (float)ts;
			}
		}
	}

	if (Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL))
	{
		m_Velocity = 10.0f;
	}
	else if (!Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL))
	{
		m_Velocity = 5.0f;
	}

};

void PlayerQuad1::OnRender()
{
	Hazel::Renderer2D::DrawQuad(m_Position, m_Size, m_Rotation, m_Color);
};