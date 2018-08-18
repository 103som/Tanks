#pragma once
#include "tank.h"
#include "game-window.h"

class GameWindow;
class Player
{
public:
	Player(Tank *in_Tank);
	~Player();

public:
	void OnKeyPressed(GameWindow *in_GameWindow, const sf::Event::KeyEvent &key);
	void OnKeyReleased(const sf::Event::KeyEvent &key);

private:
	Tank *m_Tank;
};
