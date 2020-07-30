#pragma once
#include "Object/Actor.h"

class Locator : public nc::Actor {
public:
	Locator() {}
	virtual eType GetType() override { return eType::PROJECTILE; }
	virtual void Update(float dt) override;
};