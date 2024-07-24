#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Events/MouseEvent.h"
#include "glm/glm/trigonometric.hpp"

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

using namespace Hazel;

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_Camera(-16.0f, 16.0f, -9, 9)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Triangle.Texture = Hazel::Texture2D::Create("assets/textures/Triangle.png");

	m_Quads.resize(3);
	for (int i = 0; i < m_Quads.size(); i++) {
		m_Quads[i].Position.x = i * 5;
		m_Quads[i].Position.y = 9;
	}
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	// Update

	if (Input::IsKeyPressed(HZ_KEY_Z))
	{
		m_Player.Rotation += 5.0f * (float)ts;
	}
	else if (Input::IsKeyPressed(HZ_KEY_X))
	{
		m_Player.Rotation -= 5.0f * (float)ts;
	}
	if (Input::IsKeyPressed(HZ_KEY_A))
	{
		m_Player.Position.x -= m_Player.Velocity * (float)ts;

		if (m_Triangle.Life > 0)
		{
			if (CollisionTestPlayerTouch())
			{
					m_Player.Position.x += m_Player.Velocity * (float)ts;
			}
		}
	}
	else if (Input::IsKeyPressed(HZ_KEY_D))
	{
		m_Player.Position.x += m_Player.Velocity * (float)ts;

		if (m_Triangle.Life > 0)
		{
			if (CollisionTestPlayerTouch())
			{
				m_Player.Position.x -= m_Player.Velocity * (float)ts;
			}
		}
	}

	if (Input::IsKeyPressed(HZ_KEY_W))
	{
		m_Player.Position.y += m_Player.Velocity * (float)ts;

		if (m_Triangle.Life > 0)
		{
			if (CollisionTestPlayerTouch())
			{
				m_Player.Position.y -= m_Player.Velocity * (float)ts;
			}
		}
	}
	else if (Input::IsKeyPressed(HZ_KEY_S))
	{
		m_Player.Position.y -= m_Player.Velocity * (float)ts;

		if (m_Triangle.Life > 0)
		{
			if (CollisionTestPlayerTouch())
			{
				m_Player.Position.y += m_Player.Velocity * (float)ts;
			}
		}
	}

	if (Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL))
	{
		m_Player.Velocity = 10.0f;
	}
	else if (!Input::IsKeyPressed(HZ_KEY_LEFT_CONTROL))
	{
		m_Player.Velocity = 5.0f;
	}

	if (Input::IsKeyPressed(HZ_KEY_Q))
	{
		m_CameraRotation += 5.0f;
	}
	else if (Input::IsKeyPressed(HZ_KEY_E))
	{
		m_CameraRotation -= 5.0f;
	}

	for (int i = 0; i < m_Ammunition.size(); i++)
	{
		if (m_Ammunition[i].Distance >= 10.0f)
		{
			m_Ammunition.erase(m_Ammunition.begin());
			m_Size--;
			m_Index--;
		}
		else
		{
			m_Ammunition[i].Position.x += cos(m_Ammunition[i].Rotation) * m_Ammunition[i].VectorLength * (float)ts;
			m_Ammunition[i].Position.y += sin(m_Ammunition[i].Rotation) * m_Ammunition[i].VectorLength * (float)ts;
			m_Ammunition[i].Distance += 0.2f;
			m_Ammunition[i].Angle -= 15.0f * (float)ts;
		}
	}

	if (CollisionTest() && m_Triangle.Life > 0)
	{
		m_Ammunition.erase(m_Ammunition.begin());
		m_Size--;
		m_Index--;

		m_Triangle.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
		m_Triangle.Size = 6.0f;
		m_Triangle.Life -= 1;
		std::cout << "Triangle life: " << m_Triangle.Life << std::endl;
	}
	else
	{
		m_Triangle.Color = { 0.0f, 0.23f, 0.0f, 1.0f };
		m_Triangle.Size = 5.0f;
	}

	float x = glm::cos(m_Angle) * 3;
	float y = glm::sin(m_Angle) * 3;
	m_Angle += 0.03f;
	
	// Update camera
	m_Camera.SetRotation(m_CameraRotation);
	m_Camera.SetPosition(m_Player.Position);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_Camera);
	Hazel::Renderer2D::DrawQuad(m_Player.Position, m_Player.Size, m_Player.Rotation, m_Player.Color);

	for (int i = 0; i < m_Quads.size(); i++) 
	{
	
		Hazel::Renderer2D::DrawQuad(m_Quads[i].Position, m_Quads[i].Size, m_Quads[i].Rotation, m_Quads[i].Color);

		if (m_Quads[i].Position.x < -9.0f)
		{
			m_Quads[i].Position.x = 9.0f;
		}

		m_Quads[i].Position.x -= 10.0f * (float)ts;
	}

	Hazel::Renderer2D::DrawQuad({ x, y, 0.0f }, { 2.0f, 2.0f },{ x, y, 0.5f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.5f }, { 20.0f, 20.0f }, m_Texture);

	for (auto& Ammo : m_Ammunition)
	{
		Hazel::Renderer2D::DrawQuad(Ammo.Position, Ammo.Size, Ammo.Rotation, Ammo.Color);
	}

	
	if (m_Triangle.Life > 0)
	{
		Hazel::Renderer2D::DrawQuad(m_Triangle.Position, { m_Triangle.Size, m_Triangle.Size }, 0.0f, m_Triangle.Texture, m_Triangle.Color);
	}

	
	Hazel::Renderer2D::EndScene();

	// TODO: Add these functions - Shader::SetMat4, Shader::SetFloat4
	// std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
	// std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Player color.", glm::value_ptr(m_Player.Color));
	ImGui::SliderFloat("Triangle size.", &m_Triangle.Size, 0.0f, 10.0f);
	if (ImGui::Button("Spawn Triangle"))
	{
		m_Triangle.Life = 10;
		m_Triangle.Active = true;
	}
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Controls");
	ImGui::Text("Walk around: WASD. \nSprint: ctrl. \nRotate the camera: QE. \nZoom in & out: Scroll wheel. \nShoot: MB1. \nReload: R\nPress ZX to rotate the player.");
	ImGui::Text(" ");
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	ImGui::Text("Collision detection with the triangle is now implemented.", 1);
	ImGui::EndChild();
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(Sandbox2D::OnMouseScrolled));
	dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(Sandbox2D::OnMouseButtonPressed));
	dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
	//dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	//m_CameraController.OnEvent(e);
}

bool Sandbox2D::OnKeyPressed(Hazel::KeyPressedEvent& e)
{
	if (e.GetKeyCode() == HZ_KEY_R)
	{
		std::cout << "Reloaded" << std::endl;
		m_Player.AmmoCount = 50;
	}

	return false;
}

bool Sandbox2D::OnMouseButtonPressed(Hazel::MouseButtonPressedEvent& e)
{
	m_Size++;
	m_Ammunition.resize(m_Size);
	m_Ammunition[m_Index].Position.x = m_Player.Position.x;
	m_Ammunition[m_Index].Position.y = m_Player.Position.y;
	m_Ammunition[m_Index].Rotation = m_Player.Rotation;
	m_Index++;

	return false;
}

bool Sandbox2D::OnMouseScrolled(Hazel::MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool Sandbox2D::CollisionTest()
{
	glm::vec4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};

	for (auto& Ammo : m_Ammunition) 
	{
		glm::vec4 playerTransformedVerts[4];
		for (int i = 0; i < 4; i++)
		{
			playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), Ammo.Position)
				* glm::rotate(glm::mat4(1.0f), Ammo.Rotation, { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), Ammo.Size)
				* playerVertices[i];
		}

		// To match Triangle.png (each corner is 10% from the texture edge)
		glm::vec4 pillarVertices[3] = {
			{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
		};

		glm::vec2 tri[3];
		// Triangle
		for (int i = 0; i < 3; i++) 
		{
			tri[i] = glm::translate(glm::mat4(1.0f), m_Triangle.Position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { m_Triangle.Size, m_Triangle.Size, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}
	
	}
	return false;
}

bool Sandbox2D::CollisionTestPlayerTouch()
{
	glm::vec4 playerVertices[4] = {
		{ -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f }
	};
	
		glm::vec4 playerTransformedVerts[4];
		for (int i = 0; i < 4; i++)
		{
			playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), m_Player.Position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), {0.0f, 0.0f, 1.0f})
				* glm::scale(glm::mat4(1.0f), m_Player.Size)
				* playerVertices[i];
		}

		// To match Triangle.png (each corner is 10% from the texture edge)
		glm::vec4 pillarVertices[3] = {
			{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
			{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
		};

		glm::vec2 tri[3];
		// Top pillars
		for (int i = 0; i < 3; i++)
		{
			tri[i] = glm::translate(glm::mat4(1.0f), m_Triangle.Position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { m_Triangle.Size, m_Triangle.Size, 1.0f })
				* pillarVertices[i];
		}

		for (auto& vert : playerTransformedVerts)
		{
			if (PointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;
		}

	return false;
}