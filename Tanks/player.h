#pragma once
#include "tank.h"
#include "application.h"

class Application;
class Player
{
public:
	Player(Tank *in_Tank);
	~Player();

public:
	void OnKeyPressed(Application *in_Application, const sf::Event::KeyEvent &key);
	void OnKeyReleased(const sf::Event::KeyEvent &key);

private:
	Tank *m_Tank;
};
