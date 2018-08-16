#include "object.h"



Object::Object() : m_Direction(sf::Vector2f(1, 0)), m_Health(1)
{
}


Object::~Object()
{
}

void Object::SetVelocity(sf::Vector2f in_Velocity)
{
	m_Velocity = in_Velocity;
	SetDirection(m_Velocity);
}

sf::Vector2f Object::GetVelocity()
{
	return m_Velocity;
}

void Object::SetDirection(sf::Vector2f in_Direction)
{
	if (in_Direction.x == 0 && in_Direction.y == 0)
		return;

	m_Direction = in_Direction;
}

sf::Vector2f Object::GetDirection()
{
	return m_Direction;
}

void Object::SetSize(sf::Vector2f in_Size)
{
	m_Size = in_Size;
	m_Sprite.setScale(in_Size.x / m_Sprite.getTextureRect().width, in_Size.y / m_Sprite.getTextureRect().height);
	m_Sprite.setOrigin(m_Sprite.getTextureRect().width / 2, m_Sprite.getTextureRect().height / 2);
}

sf::Vector2f Object::GetSize()
{
	return m_Size;
}

void Object::SetPos(sf::Vector2f in_Pos)
{
	m_Pos = in_Pos;
}

sf::Vector2f Object::GetPos()
{
	return m_Pos;
}

bool Object::CheckIntersect(Object *in_Object, sf::Time in_Time)
{
	if (CheckIntersectX(in_Object, in_Time))
		return true;

	if (CheckIntersectY(in_Object, in_Time))
		return true;

	return false;
}

bool Object::CheckIntersectX(Object *in_Object, sf::Time in_Time)
{
	if (fabs(in_Object->GetPos().y - this->GetPos().y) > (in_Object->GetSize().y + this->GetSize().y) / 2)
		return false;

	// ������ ������ ����� �� ������� �������
	if (this->GetPos().x + this->GetSize().x / 2 <= in_Object->GetPos().x - in_Object->GetSize().x / 2)
		if (this->GetPos().x + this->GetSize().x / 2 >= in_Object->GetPos().x - in_Object->GetSize().x / 2 + in_Object->GetVelocity().x * in_Time.asMilliseconds())
			return true;

	// ������ ������ ������ �� ������� �������
	if (this->GetPos().x - this->GetSize().x / 2 >= in_Object->GetPos().x + in_Object->GetSize().x / 2)
		if (this->GetPos().x - this->GetSize().x / 2 <= in_Object->GetPos().x + in_Object->GetSize().x / 2 + in_Object->GetVelocity().x * in_Time.asMilliseconds())
			return true;

	return false;
}

bool Object::CheckIntersectY(Object *in_Object, sf::Time in_Time)
{
	if (fabs(in_Object->GetPos().x - this->GetPos().x) > (in_Object->GetSize().x + this->GetSize().x) / 2)
		return false;

	// ������ ������ ���� ������� �������
	if (this->GetPos().y - this->GetSize().y / 2 >= in_Object->GetPos().y + in_Object->GetSize().y / 2)
		if (this->GetPos().y - this->GetSize().y / 2 <= in_Object->GetPos().y + in_Object->GetSize().y / 2 + in_Object->GetVelocity().y * in_Time.asMilliseconds())
			return true;

	// ������ ������ ���� ������� �������
	if (this->GetPos().y + this->GetSize().y / 2 <= in_Object->GetPos().y - in_Object->GetSize().y / 2)
		if (this->GetPos().y + this->GetSize().y / 2 >= in_Object->GetPos().y - in_Object->GetSize().y / 2 + in_Object->GetVelocity().y * in_Time.asMilliseconds())
			return true;

	return false;
}

void Object::Draw(sf::RenderWindow *in_Window)
{
	m_Sprite.setPosition(GetPos());
	in_Window->draw(m_Sprite);
}

void Object::SetTexture(const char *in_FileName)
{
	m_Texture.loadFromFile(in_FileName);
	m_Sprite = sf::Sprite(m_Texture);
	m_Sprite.setOrigin(m_Sprite.getTextureRect().width / 2, m_Sprite.getTextureRect().height / 2);
}

void Object::SetHealth(int in_Health)
{
	m_Health = in_Health;
}

int Object::GetHealth()
{
	return m_Health;
}
