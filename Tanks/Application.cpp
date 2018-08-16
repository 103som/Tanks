#include "application.h"
#include "SFML/System/Clock.hpp"
#include "tank.h"
#include "wall.h"
#include "missile.h"

Application::Application() : m_ObjectsCount(0)
{
	m_Width = 1920;
	m_Height = 1080;
	m_Window = new sf::RenderWindow(sf::VideoMode(m_Width, m_Height), "U will lose");
	GenerateLevel();
}


Application::~Application()
{
}

void Application::Execute()
{
	sf::Clock clock;
	sf::Time lastTime = clock.getElapsedTime();

	while (m_Window->isOpen())
	{
		sf::Time currentTime = clock.getElapsedTime();
		Update(currentTime - lastTime);
		Draw();
		HandleEvents();

		lastTime = currentTime;
	}
}

bool Application::GenerateLevel()
{
	Tank *tank = new Tank();
	tank->SetPos(sf::Vector2f(100, 100));
	AddObject(tank);
	m_Player = new Player(tank);

	Tank *enemy = new Tank();
	enemy->SetPos(sf::Vector2f(600, 600));
	AddObject(enemy);

	Wall *wall1 = new Wall();
	wall1->SetPos(sf::Vector2f(0, m_Height / 2));
	wall1->SetSize(sf::Vector2f(0, m_Height));
	wall1->SetHealth(99999);
	AddObject(wall1);

	Wall *wall2 = new Wall();
	wall2->SetPos(sf::Vector2f(m_Width / 2, m_Height));
	wall2->SetSize(sf::Vector2f(m_Width, 0));
	wall2->SetHealth(99999);
	AddObject(wall2);

	Wall *wall3 = new Wall();
	wall3->SetPos(sf::Vector2f(m_Width, m_Height / 2));
	wall3->SetSize(sf::Vector2f(0, m_Height));
	wall3->SetHealth(99999);
	AddObject(wall3);

	Wall *wall4 = new Wall();
	wall4->SetPos(sf::Vector2f(m_Width / 2, 0));
	wall4->SetSize(sf::Vector2f(m_Width, 0));
	wall4->SetHealth(99999);
	AddObject(wall4);

	return true;
}

void Application::Update(sf::Time in_Time)
{
	// Удаление объектов (Кол-во жизней)
	for (int i = 0; i < m_ObjectsCount; ++i)
		if (m_Objects[i]->GetHealth() == 0)
			RemoveObject(m_Objects[i--]);

	// Перемещение объектов и уведомление о столкновениях
	for (int i = 0; i < m_ObjectsCount; ++i)
	{
		sf::Vector2f velocity = m_Objects[i]->GetVelocity();

		sf::Vector2f pos = m_Objects[i]->GetPos();

		Object *nearestX = getNearestIntersectX(m_Objects[i], in_Time);

		if (nearestX == NULL)
			pos.x += velocity.x * in_Time.asMilliseconds();
		else
		{
			if (m_Objects[i]->GetPos().x > nearestX->GetPos().x)
				pos.x = (nearestX->GetPos().x + nearestX->GetSize().x / 2) + m_Objects[i]->GetSize().x / 2;
			else
				pos.x = (nearestX->GetPos().x - nearestX->GetSize().x / 2) - m_Objects[i]->GetSize().x / 2;
		}

		Object *nearestY = getNearestIntersectY(m_Objects[i], in_Time);
		if (nearestY == NULL)
			pos.y += velocity.y * in_Time.asMilliseconds();
		else
		{
			if (m_Objects[i]->GetPos().y > nearestY->GetPos().y)
				pos.y = (nearestY->GetPos().y + nearestY->GetSize().y / 2) + m_Objects[i]->GetSize().y / 2;
			else
				pos.y = (nearestY->GetPos().y - nearestY->GetSize().y / 2) - m_Objects[i]->GetSize().y / 2;
		}

		// Вызов события столкновения
		if (nearestX != NULL)
			m_Objects[i]->OnIntersect(nearestX);

		if (nearestY != NULL)
			m_Objects[i]->OnIntersect(nearestY);

		m_Objects[i]->SetPos(pos);
	}
}

void Application::Draw()
{
	m_Window->clear();

	for (int i = 0; i < m_ObjectsCount; ++i)
		m_Objects[i]->Draw(m_Window);

	m_Window->display();
}

void Application::HandleEvents()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_Window->close();

		if (event.type == sf::Event::KeyPressed)
			m_Player->OnKeyPressed(this, event.key);
		else if (event.type == sf::Event::KeyReleased)
			m_Player->OnKeyReleased(event.key);
	}
}

Object *Application::getNearestIntersectX(Object *in_Object, sf::Time in_Time)
{
	Object *nearest = NULL;
	for (int i = 0; i < m_ObjectsCount; ++i)
	{
		if (!m_Objects[i]->CheckIntersectX(in_Object, in_Time))
			continue;

		if (nearest == NULL || fabs(in_Object->GetPos().x - m_Objects[i]->GetPos().x) < fabs(nearest->GetPos().x - in_Object->GetPos().x))
			nearest = m_Objects[i];
	}

	return nearest;
}

Object *Application::getNearestIntersectY(Object *in_Object, sf::Time in_Time)
{
	Object *nearest = NULL;
	for (int i = 0; i < m_ObjectsCount; ++i)
	{
		if (!m_Objects[i]->CheckIntersectY(in_Object, in_Time))
			continue;

		if (nearest == NULL || fabs(in_Object->GetPos().y - m_Objects[i]->GetPos().y) < fabs(nearest->GetPos().y - in_Object->GetPos().y))
			nearest = m_Objects[i];
	}

	return nearest;
}

void Application::AddObject(Object *in_Object)
{
	Object **tempObjects = m_Objects;

	m_ObjectsCount += 1;
	m_Objects = new Object*[m_ObjectsCount];

	for (int i = 0; i < m_ObjectsCount - 1; ++i)
		m_Objects[i] = tempObjects[i];
	delete[] tempObjects;

	m_Objects[m_ObjectsCount - 1] = in_Object;
}

void Application::RemoveObject(Object *in_Object)
{
	int objectNum = -1;
	for (int i = 0; i < m_ObjectsCount; ++i)
		if (in_Object == m_Objects[i])
			objectNum = i;

	if (objectNum == -1)
		return;
	
	delete m_Objects[objectNum];
	m_Objects[objectNum] = m_Objects[m_ObjectsCount - 1];
	m_ObjectsCount -= 1;
}
