#include "TrianglePlayer.h"

using namespace Hazel;

void TrianglePlayer::LoadAssets()
{
	m_TriangleTexture = Texture2D::Create("assets/textures/Triangle.png");
}

void TrianglePlayer::OnUpdate(Hazel::Timestep ts)
{
	if (Input::IsKeyPressed(HZ_KEY_LEFT))
	{
		m_Rotation += 6.0f * (float)ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_RIGHT))
	{
		m_Rotation -= 6.0f * (float)ts;
	}

	if (Input::IsKeyPressed(HZ_KEY_RIGHT_CONTROL))
	{
		m_Velocity = 5.0f * 1.5f;
	}
	else if (!Input::IsKeyPressed(HZ_KEY_RIGHT_CONTROL))
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

	if (Input::IsKeyPressed(HZ_KEY_UP))
	{
		m_Position.x += cos(m_Rotation + 1.57f)  * m_Velocity * (float)ts;
		m_Position.y += sin(m_Rotation + 1.57f) * m_Velocity * (float)ts;
	}

	if (Input::IsKeyPressed(HZ_KEY_DOWN))
	{
		m_Position.x -= cos(m_Rotation + 1.57f) * m_Velocity * (float)ts;
		m_Position.y -= sin(m_Rotation + 1.57f) * m_Velocity * (float)ts;
	}

}

void TrianglePlayer::OnRender()
{
	Renderer2D::DrawQuad({ m_Position.x, m_Position.y, 0.5f }, m_Size, m_Rotation, m_TriangleTexture, { 0.3f, 0.3f, 0.3f, 1.0f });
}

void TrianglePlayer::OnImGuiRender()
{

}

void TrianglePlayer::Reset()
{
	m_Position = { 6.0f, 6.0f, 0.0f };
	m_Rotation = 59.7f;
}