#pragma once
#include <string>
#include <iostream>
#include <functional>
#include "../../Core/EC/Component.h"

enum class CardEntityUniqueID {
	TEST_CARD,
	TEST_CARD_2,
	// It's important to keep this one at the end. The order matters to a function that creates a random card entity using a random ID
	UNDEFINED
};

enum class CardTargetType
{
	SELF,
	ENEMY,
	ALL_ENEMIES,
	ALL,
	UNDEFINED
};

enum class CardType
{
	ATTACK,
	DEFENSE,
	BUFF,
	DEBUFF,
	UNDEFINED
};

struct CardConfiguration {
	CardEntityUniqueID uniqueID = CardEntityUniqueID::UNDEFINED;
	std::string name = "UNDEFINED";
	std::string description = "UNDEFINED";
	// first int is the number of dices to roll, second int is the number of sides on the dices
	std::pair <int, int> diceRoll = { 0, 0 };
	// first int is the modifier to add to number of dices, second int is the modifier to add to number of sides on the dices
	std::pair <int, int> diceModifiers = { 0, 0 };
	CardType cardType = CardType::UNDEFINED;
	CardTargetType targetType = CardTargetType::UNDEFINED;
	int cost = 0;
	std::function<void()> effect = []() {};
};

class CardComponent : public Component
{
	friend class CardEntityBuilder;

public:
	CardComponent(CardConfiguration cardConfiguration);
	~CardComponent();

	// Inherited via Component
	void Init() override;
	void Update(const float deltaTime) override;
	void Render() override;

	friend std::ostream& operator<<(std::ostream& os, const CardComponent& card);

private:
	CardConfiguration _cardConfiguration;
};

