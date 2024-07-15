#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "GameLayer.h"
#include "Sandbox2D/Sandbox2D.h"
#include "2DGame/2DGameLayer.h"
 

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new GameLayer2D());
		//PushLayer(new GameLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}