#include "Map.h"

#include <glm/gtc/matrix_transform.hpp>
#include "RandomNumber.h"
using namespace Hazel;

static bool PointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}

void Map::Init()
{
	m_FloorTexture = Texture2D::Create("assets/textures/Checkerboard.png");
	m_TrianglePlayer.LoadAssets();
}

void Map::OnUpdate(Hazel::Timestep ts)
{
	m_Time -= (float)ts;

	if (CollisionTest())
	{
		GameOver();
		return;
	}

	m_QuadPlayer.OnUpdate(ts);
	m_TrianglePlayer.OnUpdate(ts);
}

void Map::OnRender()
{
	// floor
	Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.3f }, { 20.0f, 20.0f }, glm::radians(0.0f), m_FloorTexture);
	
	m_QuadPlayer.OnRender();
	m_TrianglePlayer.OnRender();
}

void Map::OnImGuiRender()
{
}

bool Map::CollisionTest()
{
	glm::vec4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	//const auto& pos = m_QuadPlayer.GetPosition();
	glm::vec4 playerTransformedVerts[4];
	for (int i = 0; i < 4; i++)
	{
		playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), m_QuadPlayer.GetPosition())
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_QuadPlayer.GetRotation()), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { m_QuadPlayer.GetSize().x, m_QuadPlayer.GetSize().y, 1.0f })
			* playerVertices[i];
	}

	// To match Triangle.png (each corner is 10% from the texture edge)
	glm::vec4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
	};

	
	glm::vec2 tri[3];
	for (int i = 0; i < 3; i++)
	{
		tri[i] = glm::translate(glm::mat4(1.0f), m_TrianglePlayer.GetPosition())
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_TrianglePlayer.GetRotation()), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { m_TrianglePlayer.GetSize().x, m_TrianglePlayer.GetSize().y, 1.0f})
			* pillarVertices[i];
	}

	for (auto& vert : playerTransformedVerts)
	{
		if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
			return true;
	}

	return false;
}

void Map::GameOver()
{
	m_GameOver = true;
}

void Map::Reset()
{
	m_GameOver = false;

	m_Time = 30.0f;
	m_QuadPlayer.Reset();
	m_TrianglePlayer.Reset();
}