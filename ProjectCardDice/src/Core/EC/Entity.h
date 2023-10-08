#pragma once
#include <vector>
#include <memory>
#include "Component.h"

class Entity
{
	friend class EntityManager;

public:
	~Entity();

	/// <summary>
	/// Runs every frame and updates the entitiy's components.
	/// </summary>
	/// <param name="deltaTime">The interval in seconds from the last frame to the current one</param>
	void Update(const float deltaTime);

	/// <summary>
	/// Runs every frame and renders the entity's components and should be called after updating the entity.
	/// </summary>
	void Render();

	/// <summary>
	/// Destroys the entity and all of its components.
	/// </summary>
	void Destroy() { _isActive = false; }

	/// <summary>
	/// Returns whether or not the entity is active.
	/// </summary>
	bool IsActive() const { return _isActive; }
	
	/// <summary>
	/// Returns whether or not the entity has a component of the given type.
	/// </summary>
	/// <typeparam name="T">The component's type</typeparam>
	template <typename T> 
	bool HasComponent() const { return _componentSignatures[GetComponentTypeID<T>()]; }

	/// <summary>
	/// Adds a component of the given type to the entity.
	/// </summary>
	/// <typeparam name="T">The component's type</typeparam>
	/// <typeparam name="...TArgs">The component's constructor arguments</typeparam>
	/// <param name="...args">The component's constructor arguments</param>
	/// <returns>Reference to the added component</returns>
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		// Create a new component and set it's owner to this entity
		std::unique_ptr<Component> componentPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
		componentPtr->_owner = this;

		// Set signature to true to indicate that this entity has this component
		ComponentTypeID ID = GetComponentTypeID<T>();
		_componentPointers[ID] = componentPtr.get();
		_componentSignatures[ID] = true;

		componentPtr->Init();

		// Add the component to the vector of components and return a reference to it
		_components.push_back(std::move(componentPtr));
		return *_components.back();
	}

	/// <summary>
	/// Returns a reference to the component of the given type.
	/// </summary>
	/// <typeparam name="T">The component's type</typeparam>
	template<typename T> T& GetComponent() const
	{
		auto ptr(_componentPointers[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	Entity();

	std::vector<std::unique_ptr<Component>> _components;
	ComponentArray _componentPointers;
	ComponentBitset _componentSignatures;
	bool _isActive;

};