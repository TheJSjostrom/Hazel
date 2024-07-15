#include "Map.h"

#include <glm/gtc/matrix_transform.hpp>
#include "RandomNumber.h"
using namespace Hazel;

void Map::Init()
{
	m_FloorTexture = Texture2D::Create("assets/textures/Checkerboard.png");

	m_Foods.resize(5);
	for (int i = 0; i < 5; i++)
		CreatePillar(i);
}

void Map::OnUpdate(Hazel::Timestep ts)
{
	m_Player.OnUpdate(ts);
}

void Map::OnRender()
{
	// floor
	Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.3f }, { 20.0f, 20.0f }, glm::radians(0.0f), m_FloorTexture);
	
	// Food
	for (auto& food : m_Foods)
	{
		Renderer2D::DrawQuad({ food.TopPosition.x, food.TopPosition.y, 0.0f }, { 1.0f, 1.0f }, glm::radians(0.0f), {0.12f, 0.5f, 1.0f, 1.0f});
	}

	m_Player.OnRender();
}

void Map::OnImGuiRender()
{

}

void Map::CreatePillar(int index)
{
	Food& food = m_Foods[index];
	food.TopPosition.x = Random::Float() * 10;
	food.TopPosition.y = Random::Float() * 10;

}

bool Map::CollisionTest()
{
	return false;
}

void Map::GameOver()
{

}

void Map::Reset()
{

}