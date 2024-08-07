#include "Entity.h"

Entity::Entity(const std::string& uniqueName) : _uniqueName{ uniqueName }, _isActive{ true }, _componentIdToPointer{}
{
}

void Entity::HandleEvents(SDL_Event& event)
{
	for (auto& component : _components) {
		component->HandleEvents(event);
	}
}

void Entity::Update(const float deltaTime)
{
	for (auto& component : _components) {
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (auto& component : _components) {
		component->Render();
	}
}

void Entity::Destroy()
{
	_isActive = false;
	std::cout << "Destroying Entity: " << "'" << _uniqueName << "'" << std::endl;
}