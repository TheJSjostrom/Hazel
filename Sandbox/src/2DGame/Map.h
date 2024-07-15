#pragma once
#include "Character.h"
#include "Hazel.h"
struct Food
{
	glm::vec3 TopPosition = { 0.0f, 10.0f, 0.0f };

};

class Map
{
public:
	void Init();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();

	void OnImGuiRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();

private:
	void CreatePillar(int index);
	bool CollisionTest();

	void GameOver();
private:

	bool m_GameOver = false;
	Character m_Player;

	std::vector<Food> m_Foods;

	Hazel::Ref<Hazel::Texture2D> m_FloorTexture;
};