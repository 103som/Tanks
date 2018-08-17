#pragma once
#include "object.h"

class Missile : public Object
{
public:
	Missile(const int in_Group);
	~Missile();

public:
	void OnIntersect(Object *in_Object);
};
