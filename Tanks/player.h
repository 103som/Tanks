#pragma once
#include "tank.h"

class Player
{
public:
	Player(Tank *in_Tank);
	~Player();

public:
	void OnKeyPressed(const sf::Event::KeyEvent &key);
	void OnKeyReleased(const sf::Event::KeyEvent &key);

private:
	Tank *m_Tank;
};

