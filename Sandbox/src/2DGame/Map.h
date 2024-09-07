#pragma once
#include "QuadPlayer.h"
#include "TrianglePlayer.h"

#include "Hazel.h"

class Map
{
public:
	void Init();

	void OnUpdate(Hazel::Timestep ts);
	void OnRender();
	void OnImGuiRender();

	bool IsGameOver() const { return m_GameOver; }
	void Reset();
	float GetTime() const { return m_Time; }

	QuadPlayer& GetQuadPlayer() { return m_QuadPlayer; }
private:
	bool CollisionTest();
	void GameOver();

private:
	QuadPlayer m_QuadPlayer;
	TrianglePlayer m_TrianglePlayer;

	Hazel::Ref<Hazel::Texture2D> m_FloorTexture;

	bool m_GameOver = false;
	float m_Time = 30.0f;
};