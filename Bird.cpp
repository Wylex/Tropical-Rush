#include "Bird.h"
#include <ctime>
#include <cstdlib>

Bird::Bird(sf::FloatRect goThroughAreaArg, Direction directionArg): windowArea(0, 0, 480, 350) {

	std::srand(time(NULL));

	direction = directionArg;
	goThroughArea = goThroughAreaArg;

	if(direction == Right) {
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

bool Bird::hasBirdCrossedArea() const {
	bool isOutOfArea = false;

	if(direction == Left) {
		if(bird.getGlobalBounds().left + bird.getGlobalBounds().width < goThroughArea.left)
			isOutOfArea = true;
	}
	else {
		if(bird.getGlobalBounds().left > goThroughArea.left + goThroughArea.width)
			isOutOfArea = true;
	}

	return isOutOfArea;
}

bool Bird::areProjectilesOutOfScene() const {
	bool areTheyOutOfArea = true;

	for(int i(0); i < projectiles.size(); i++) {
		sf::FloatRect projectilePos = projectiles[i].getGlobalBounds();
		if(projectilePos.left > 0 and projectilePos.left + projectilePos.width < windowArea.width and projectilePos.top + projectilePos.height < windowArea.height)
			areTheyOutOfArea = false;
	}

	return areTheyOutOfArea;
}

bool Bird::isVisible() const {
	return (!hasBirdCrossedArea() and areProjectilesOutOfScene());
}

void Bird::move(int speed) {
	if(direction == Left)
		bird.move(-speed, 0);
	else
		bird.move(speed, 0);
}

std::vector<sf::FloatRect> Bird::getProjectileBounds() const {
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
