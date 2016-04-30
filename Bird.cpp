#include "Bird.h"
#include <ctime>
#include <cstdlib>

Bird::Bird(sf::FloatRect goThroughArea, Direction directionArg) {

	std::srand(time(NULL));

	direction = directionArg;

	if(direction == Left) {
		birdTexture.loadFromFile("");
		bird.setTexture(birdTexture);
		bird.setPosition(0 - bird.getGlobalBounds().width, 0);
	}
	else {
		birdTexture.loadFromFile("");
		bird.setTexture(birdTexture);
		bird.setPosition(goThroughArea.width, 0);
	}

	int birdHeight = bird.getGlobalBounds().height;
	int yPosition = std::rand()%int(goThroughArea.height - birdHeight) + goThroughArea.top;

	bird.move(0, yPosition);
}

void Bird::move(int speed) {
	if(direction == Left)
		bird.move(-speed, 0);
	else
		bird.move(speed, 0);
}

std::vector<sf::FloatRect> Bird::getGlobalBounds() const {
	std::vector<sf::FloatRect> projectilesBounds;

	for(int i(0); i < projectiles.size(); i++)
		projectilesBounds.push_back(projectiles[i].getGlobalBounds());

	return projectilesBounds;
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(int i(0); i < projectiles.size(); i++)
		target.draw(projectiles[i], states);

	target.draw(bird, states);
}
