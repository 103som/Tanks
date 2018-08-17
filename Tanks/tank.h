#pragma once
#include "object.h"
#include "missile.h"

class Tank : public Object
{
public:
	Tank(const int in_Group = GROUP_COMPUTER);
	~Tank();

public:
	Missile *Fire();

	void OnIntersect(Object *in_Object);
};
