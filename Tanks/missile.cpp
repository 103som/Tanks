#include "missile.h"

Missile::Missile()
{
	SetTexture("Images/missile.png");
	SetSize(sf::Vector2f(30, 30));
}


Missile::~Missile()
{
}

void Missile::OnIntersect(Object *in_Object)
{
	in_Object->SetHealth(in_Object->GetHealth() - 1);
	this->SetHealth(GetHealth() - 1);
}
