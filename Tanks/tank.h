#pragma once
#include "object.h"
#include "missile.h"

class Tank : public Object
{
public:
	Tank();
	~Tank();

public:
	Missile *Fire();

	void OnIntersect(Object *in_Object);
};
