#pragma once

#include "Hazel.h"

#include "Map.h"
#include <imgui/imgui.h>


class GameLayer2D : public Hazel::Layer
{
public:
	GameLayer2D();
	virtual ~GameLayer2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;
	bool OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e);
	bool OnWindowResize(Hazel::WindowResizeEvent& e);
private:
	void CreateCamera(uint32_t width, uint32_t height);
private:
	Hazel::Scope<Hazel::OrthographicCamera> m_Camera;
	Map m_Map;
	ImFont* m_Font;
	float m_Time = 0.0f;
	

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;
};