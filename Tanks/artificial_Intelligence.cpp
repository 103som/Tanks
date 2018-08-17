#include "artificial_Intelligence.h"



ArtificialIntelligence::ArtificialIntelligence()
{
}


ArtificialIntelligence::~ArtificialIntelligence()
{
}

void ArtificialIntelligence::Update(Application *in_App)
{
	for (int i = 0; i < in_App->GetObjectsCount(); ++i)
	{
		Object *current = in_App->GetObject(i);
		if (current->GetGroup() != GROUP_COMPUTER)
			continue;

		if (dynamic_cast<Tank*>(current) == NULL)
			continue;

		if (current->GetVelocity() == sf::Vector2f(0, 0))
			GenerateVelocity(current);

		if (1 + rand() % 80 == 75)
		{
			Object *missile = dynamic_cast<Tank*>(current)->Fire();
			in_App->AddObject(missile);
		}
	}
}

void ArtificialIntelligence::GenerateVelocity(Object* in_Object)
{
	int direction = 1 + rand() % 2;
	int coordinateExis = 1 + rand() % 2;

	sf::Vector2f velocity;
	if (direction == 1)
		if (coordinateExis == 1)
			velocity = sf::Vector2f(1, 0);
		else
			velocity = sf::Vector2f(-1, 0);
	else if (coordinateExis == 2)
			velocity = sf::Vector2f(0, 1);
		else
			velocity = sf::Vector2f(0, -1);
	in_Object->SetVelocity(velocity);
}
