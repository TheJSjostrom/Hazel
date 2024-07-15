#include "2DGameLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "RandomNumber.h"

using namespace Hazel;

GameLayer2D::GameLayer2D()
	: Layer("GameLayer")
{
	auto& window = Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer2D::OnAttach()
{
	m_Map.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer2D::OnDetach()
{
}

void GameLayer2D::OnUpdate(Hazel::Timestep ts)
{
	m_Time += ts;

	/*
	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;
	*/
	switch (m_State)
	{
	case GameState::Play:
	{
		//m_Level.OnUpdate(ts);
		break;
	}
	}
	m_Map.OnUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.02f, 0.02f, 0.02f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(*m_Camera);
	m_Map.OnRender();
	Hazel::Renderer2D::EndScene();
}

void GameLayer2D::OnImGuiRender()
{
	//ImGui::Begin("Settings");
	//m_Level.OnImGuiRender();
	//ImGui::End();

	// UI?
/*
	switch (m_State)
	{
	case GameState::Play:
	{
		uint32_t playerScore = m_Level.GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		break;
	}
	case GameState::MainMenu:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
		break;
	}
	case GameState::GameOver:
	{
		auto pos = ImGui::GetWindowPos();
		auto width = Application::Get().GetWindow().GetWidth();
		auto height = Application::Get().GetWindow().GetHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

		pos.x += 200.0f;
		pos.y += 150.0f;
		uint32_t playerScore = m_Level.GetPlayer().GetScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
	*/
}

void GameLayer2D::OnEvent(Hazel::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(GameLayer2D::OnWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(GameLayer2D::OnMouseButtonPressed));
}

bool GameLayer2D::OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
	//	m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer2D::OnWindowResize(Hazel::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer2D::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / (float)height;

	float camWidth = 11.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = CreateScope<OrthographicCamera>(left, right, bottom, top);
}