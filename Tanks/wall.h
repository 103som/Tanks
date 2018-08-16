#pragma once
#include "object.h"

class Wall : public Object
{
public:
	Wall();
	~Wall();

public:
	void OnIntersect(Object *in_Object);
};
