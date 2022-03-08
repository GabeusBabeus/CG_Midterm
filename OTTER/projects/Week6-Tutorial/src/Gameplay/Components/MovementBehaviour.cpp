#include "Gameplay/Components/MovementBehaviour.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include "Application/Application.h"

void MovementBehaviour::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr)
	{
		IsEnabled = false;
	}
}

void MovementBehaviour::RenderImGui()
{
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &_impulse, 1.0f);
}

nlohmann::json MovementBehaviour::ToJson() const
{
	return
	{
		{ "impulse", _impulse }
	};
}

MovementBehaviour::MovementBehaviour() : IComponent(), _impulse(5.0f)
{ }

MovementBehaviour::~MovementBehaviour() = default;

MovementBehaviour::Sptr MovementBehaviour::FromJson(const nlohmann::json & blob)
{
	MovementBehaviour::Sptr result = std::make_shared<MovementBehaviour>();
	result->_impulse = blob["impulse"];
	return result;
}

void MovementBehaviour::Update(float deltaTime)
{
	bool pressed = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_W);
	if (pressed)
	{
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(_impulse, 0.0f, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, -90.0f));
		}
		_isPressed = pressed;
	}
	else
	{
		_isPressed = false;
	}

	bool pressed1 = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_S);
	if (pressed1)
	{
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(-_impulse, 0.0f, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, 90.0f));
		}
		_isPressed = pressed1;
	}
	else
	{
		_isPressed = false;
	}

	bool pressed2 = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_A);
	if (pressed2)
	{
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(0.0f, _impulse, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
		}
		_isPressed = pressed2;
	}
	else
	{
		_isPressed = false;
	}

	bool pressed3 = glfwGetKey(Application::Get().GetWindow(), GLFW_KEY_D);
	if (pressed3)
	{
		if (_isPressed == false)
		{
			_body->SetLinearVelocity(glm::vec3(0.0f, -_impulse, 0.0f));
			GetGameObject()->SetRotation(glm::vec3(90.0f, 0.0f, 180.0f));
		}
		_isPressed = pressed3;
	}
	else
	{
		_isPressed = false;
	}

	if (pressed == false && pressed1 == false)
	{
		if (pressed2 == false && pressed3 == false)
		{
			_body->SetLinearVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}