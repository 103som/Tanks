#include "missile.h"

Missile::Missile(const int in_Group) : Object(in_Group)
{
	SetTexture("Images/missile.png");
	SetSize(sf::Vector2f(30, 30));
}


Missile::~Missile()
{
}

void Missile::OnIntersect(Object *in_Object)
{
	if (in_Object->GetGroup() != this->GetGroup()) 
		in_Object->SetHealth(in_Object->GetHealth() - 1);

	this->SetHealth(GetHealth() - 1);
}
