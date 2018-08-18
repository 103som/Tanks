#pragma once
#include "game-window.h"
#include "tank.h"

class GameWindow;
class ArtificialIntelligence
{
public:
	ArtificialIntelligence();
	~ArtificialIntelligence();

public:
	void Update(GameWindow *in_GameWindow);
	void GenerateVelocity(Object* in_Object);
};

