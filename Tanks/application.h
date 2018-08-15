#pragma once
#include "player.h"
#include "object.h"
#include "SFML/Graphics.hpp"

class Application
{
public:
	Application();
	~Application();

public:
	void Execute();
	bool GenerateLevel();
	void Update(sf::Time in_Time);
	void Draw();
	void HandleEvents();

private:
	Object *getNearestIntersectX(Object *in_Object, sf::Time in_Time);
	Object *getNearestIntersectY(Object *in_Object, sf::Time in_Time);

private:
	sf::RenderWindow *m_Window;
	int m_Width;
	int m_Height;

	Player *m_Player;

	int m_ObjectsCount;
	Object **m_Objects;
};
