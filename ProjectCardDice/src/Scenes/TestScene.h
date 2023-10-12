#pragma once
#include "Scene.h"
#include "../Math/Vector2D.h"

class TestScene : public Scene
{
public:
	TestScene(Vector2D position, float speed);
	~TestScene();

	// Inherited via Scene
	void Init() override;
	void HandleEvents(union SDL_Event& event) override;
	void Update(const float deltaTime) override;
	void Render() override;
	void Destroy() override;

private:
	class Entity* _testEntity;
    Vector2D _testEntityPosition;
	float _testEntitySpeed = 0;
};

