#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

class Object
{
public:
	Object();
	~Object();

public:
	void Draw(sf::RenderWindow *in_Window);

	bool CheckIntersect(Object *in_Object, sf::Time in_Time);
	bool CheckIntersectX(Object *in_Object, sf::Time in_Time);
	bool CheckIntersectY(Object *in_Object, sf::Time in_Time);

	void SetVelocity(sf::Vector2f in_Velocity);
	sf::Vector2f GetVelocity();

	void SetSize(sf::Vector2f in_Size);
	sf::Vector2f GetSize();

	void SetPos(sf::Vector2f in_Pos);
	sf::Vector2f GetPos();

	void SetTexture(const char *in_FileName);

private:
	sf::Vector2f m_Pos; // Текущая позиция
	sf::Vector2f m_Size; // Размер
	sf::Vector2f m_Velocity; // Скорость

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};

