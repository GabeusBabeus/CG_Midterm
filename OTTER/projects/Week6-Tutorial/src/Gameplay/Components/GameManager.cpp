#include "Gameplay/Components/GameManager.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"

GameManager::GameManager() :
	IComponent(),
	_renderer(nullptr),
	EnterMaterial(nullptr),
	ExitMaterial(nullptr)
{ }
GameManager::~GameManager() = default;

void GameManager::OnEnteredTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	if (_renderer && EnterMaterial) {
		_renderer->SetMaterial(EnterMaterial);
	}
	LOG_INFO("Entered trigger: {}", trigger->GetGameObject()->Name);
}

void GameManager::OnLeavingTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	if (_renderer && ExitMaterial) {
		_renderer->SetMaterial(ExitMaterial);
	}
	LOG_INFO("Left trigger: {}", trigger->GetGameObject()->Name);
}

void GameManager::Awake() {
	_renderer = GetComponent<RenderComponent>();
}

void GameManager::RenderImGui() { }

nlohmann::json GameManager::ToJson() const {
	return {
		{ "enter_material", EnterMaterial != nullptr ? EnterMaterial->GetGUID().str() : "null" },
		{ "exit_material", ExitMaterial != nullptr ? ExitMaterial->GetGUID().str() : "null" }
	};
}

GameManager::Sptr GameManager::FromJson(const nlohmann::json& blob) {
	GameManager::Sptr result = std::make_shared<GameManager>();
	result->EnterMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["enter_material"]));
	result->ExitMaterial  = ResourceManager::Get<Gameplay::Material>(Guid(blob["exit_material"]));
	return result;
}
