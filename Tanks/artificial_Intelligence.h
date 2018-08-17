#pragma once
#include "application.h"
#include "tank.h"

class Application;
class ArtificialIntelligence
{
public:
	ArtificialIntelligence();
	~ArtificialIntelligence();

public:
	void Update(Application *in_App);
	void GenerateVelocity(Object* in_Object);
};

