#pragma once
#include "object.h"

class Missile : public Object
{
public:
	Missile();
	~Missile();

public:
	void OnIntersect(Object *in_Object);
};
