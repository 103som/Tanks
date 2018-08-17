#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

const int GROUP_NONE = 0;
const int GROUP_PLAYER = 1;
const int GROUP_COMPUTER = 3;

class Object
{
public:
	Object(const int in_Group = GROUP_NONE);
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

	void SetDirection(sf::Vector2f in_Direction);
	sf::Vector2f GetDirection();

	void SetTexture(const char *in_FileName);

	virtual void OnIntersect(Object *in_Object) = 0;

	void SetHealth(int in_Health);
	int GetHealth();

	int GetGroup();

private:
	sf::Vector2f m_Pos; // Текущая позиция
	sf::Vector2f m_Size; // Размер
	sf::Vector2f m_Velocity; // Скорость
	sf::Vector2f m_Direction; // Направление

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	int m_Health;
	int m_Group;
};
