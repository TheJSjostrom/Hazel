#pragma once

#include "Hazel.h"
#include <imgui/imgui.h>

struct Ammunition {
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Size = { 0.3f, 0.3f, 1.0f };
	glm::vec4 Color = { 0.877f, 0.595f, 0.138f, 1.0f };

	float Velocity = 10.0f;
	float Distance = 0.0f;
	float Rotation = 0.0f;
};

struct Quad
{
	glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
	glm::vec2 Size = { 2.0f, 2.0f };
	glm::vec4 Color = { 1.8f, 0.2f, 0.3f, 1.0f };

	float Rotation = 0.0f;
};

struct PlayerQuad
{
	glm::vec3 Position = { 1.0f, 1.0f, 0.0f };
	glm::vec4 Color = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec3 Size = { 0.75f, 0.75f, 1.0f };

	int AmmoCount = 50;
	float Velocity = 2.0f;
};

struct Triangle
{
	glm::vec3 Position = { 0.0f, -5.0f, 0.0f };
	glm::vec4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	Hazel::Ref<Hazel::Texture2D> Texture;

	float Size = 5.0f;
	int Life = 10;
	bool Active = true;
};

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& e) override;
private:
	bool OnKeyPressed(Hazel::KeyPressedEvent& e);
	bool OnMouseScrolled(Hazel::MouseScrolledEvent& e);
	bool OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e);
	bool CollisionTest();
	bool CollisionTestPlayerTouch();
private:
	Hazel::OrthographicCamera m_Camera;
	float m_CameraRotation = 0.0f;
	float m_AspectRatio = 16.0f/9.0f;
	float m_ZoomLevel = 9.0f;

	float m_Angle = 0.0f;
	float m_Target = -10.0f;

	Hazel::Ref<Hazel::Texture2D> m_Texture;

	int m_Size = 0;
	int m_Index = 0;
	std::vector<Ammunition> m_Ammunition; 

	std::vector<Quad> m_Quads;

	PlayerQuad m_Player;

	Triangle m_Triangle;

	std::vector<Triangle> m_Triangle2;
	// Temp
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;

};