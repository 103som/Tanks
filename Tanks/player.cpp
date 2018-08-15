#include "player.h"

Player::Player(Tank *in_Tank) : m_Tank(in_Tank)
{
}


Player::~Player()
{
}

void Player::OnKeyPressed(const sf::Event::KeyEvent &key)
{
	switch (key.code)
	{
		case sf::Keyboard::Left:
			m_Tank->SetVelocity(sf::Vector2f(-1, 0));
			break;

		case sf::Keyboard::Right:
			m_Tank->SetVelocity(sf::Vector2f(1, 0));
			break;

		case sf::Keyboard::Down:
			m_Tank->SetVelocity(sf::Vector2f(0, 1));
			break;

		case sf::Keyboard::Up:
			m_Tank->SetVelocity(sf::Vector2f(0, -1));
			break;
	}
}

void Player::OnKeyReleased(const sf::Event::KeyEvent &key)
{
	m_Tank->SetVelocity(sf::Vector2f(0, 0));
}