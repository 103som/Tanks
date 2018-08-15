#include "application.h"
#include "SFML/System/Clock.hpp"
#include "tank.h"
#include "wall.h"

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
	m_ObjectsCount = 6;
	m_Objects = new Object*[m_ObjectsCount];
	Tank *tank = new Tank();
	m_Objects[0] = tank;
	m_Objects[0]->SetPos(sf::Vector2f(100, 100));
	m_Player = new Player(tank);

	m_Objects[1] = new Tank();
	m_Objects[1]->SetPos(sf::Vector2f(600, 600));

	m_Objects[2] = new Wall();
	m_Objects[2]->SetPos(sf::Vector2f(0, m_Height / 2));
	m_Objects[2]->SetSize(sf::Vector2f(0, m_Height));

	m_Objects[3] = new Wall();
	m_Objects[3]->SetPos(sf::Vector2f(m_Width / 2, m_Height));
	m_Objects[3]->SetSize(sf::Vector2f(m_Width, 0));

	m_Objects[4] = new Wall();
	m_Objects[4]->SetPos(sf::Vector2f(m_Width, m_Height / 2));
	m_Objects[4]->SetSize(sf::Vector2f(0, m_Height));

	m_Objects[5] = new Wall();
	m_Objects[5]->SetPos(sf::Vector2f(m_Width / 2, 0));
	m_Objects[5]->SetSize(sf::Vector2f(m_Width, 0));

	return true;
}

void Application::Update(sf::Time in_Time)
{
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
			m_Player->OnKeyPressed(event.key);
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