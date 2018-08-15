#include "tank.h"
#include "SFML/Graphics.hpp"


Tank::Tank()
{
	SetTexture("Images/tank.png");
	SetSize(sf::Vector2f(50, 50));
}


Tank::~Tank()
{
}
