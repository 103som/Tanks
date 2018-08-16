#include "wall.h"

Wall::Wall() 
{
	SetTexture("Images/wall.png");
	SetSize(sf::Vector2f(50, 50));
	SetHealth(3);
}


Wall::~Wall()
{
}

void Wall::OnIntersect(Object *in_Object)
{
	this->SetHealth(GetHealth() - 1);
}
