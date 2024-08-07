#pragma once
#include "../../Core/EC/Scene.h"
#include "../../Core/Math/Vector2D.h"

class TestScene : public Scene
{
public:
	TestScene(Vector2D position, float speed);

	// Inherited via Scene
	void Init() override;
	void HandleEvents(union SDL_Event& event) override;
	void Update(const float deltaTime) override;

private:
	Entity* _testEntity;
	Entity* _cardEntity;
    Vector2D _testEntityPosition;
	float _testEntitySpeed = 0;
};

