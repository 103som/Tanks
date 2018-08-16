#include "tank.h"
#include "SFML/Graphics.hpp"


Tank::Tank()
{
	SetHealth(3);
	SetTexture("Images/tank.png");
	SetSize(sf::Vector2f(50, 50));
}


Tank::~Tank()
{
}

Missile* Tank::Fire()
{
	Missile *missile = new Missile;
	const int size = missile->GetSize().x / 2;

	missile->SetPos(sf::Vector2f(GetPos().x + GetSize().x / 2 * GetDirection().x + GetDirection().x * size, GetPos().y + GetSize().y / 2 * GetDirection().y + GetDirection().y * size));

	missile->SetVelocity(this->GetDirection());

	return missile;
}

void Tank::OnIntersect(Object *in_Object)
{

}
