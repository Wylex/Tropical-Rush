#include "Bird.h"
#include <ctime>
#include <cstdlib>
#include <string>

Bird::Bird(const TexturesHolder& textureHolder, Direction directionArg) {

	std::srand(time(NULL));

	direction = directionArg;
	animationSpriteFrame = 0;
	windowArea = sf::FloatRect(0, 0, 480, 350);
	goThroughArea = sf::FloatRect(0, 0, 0, 0);

	buildBird(textureHolder);
}

void Bird::buildBird(const TexturesHolder& textureHolder) {
	const int numberOfFrames = 10;
	setSpriteNumber(numberOfFrames);
	setBirdTextures(textureHolder, numberOfFrames);
	setBirdInitialPosition();
}

void Bird::setSpriteNumber(int numFrames) {
	birds.resize(numFrames);
}

void Bird::setBirdTextures(const TexturesHolder& textures, int numFrames) {
	std::vector<std::shared_ptr<sf::Texture>> textures_ptr;
	if(direction == Left)
		textures_ptr = textures.get(TexturesHolder::BirdLeft);
	else
		textures_ptr = textures.get(TexturesHolder::BirdRight);

	for(int i(0); i < numFrames; i++) {
		std::shared_ptr<sf::Texture> texture_ptr{textures_ptr[i]};
		birds[i].setTexture(*texture_ptr);
	}
}

void Bird::setBirdInitialPosition() {
	if(direction == Right)
		birds[animationSpriteFrame].setPosition(goThroughArea.left - birds[0].getGlobalBounds().width, 0);
	else
		birds[animationSpriteFrame].setPosition(goThroughArea.width, 0);

	int birdHeight = birds[0].getGlobalBounds().height;
	int yPosition = std::rand()%int(goThroughArea.height - birdHeight) + goThroughArea.top;

	birds[animationSpriteFrame].move(0, yPosition);
}

bool Bird::isVisible() const {
	return (!hasBirdCrossedArea() and areProjectilesOutOfScene());
}

bool Bird::hasBirdCrossedArea() const {
	bool isOutOfArea = false;

	sf::FloatRect birdBounds = birds[animationSpriteFrame].getGlobalBounds();
	if(direction == Left) {
		if(birdBounds.left + birdBounds.width < goThroughArea.left)
			isOutOfArea = true;
	}
	else {
		if(birdBounds.left > goThroughArea.left + goThroughArea.width)
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

void Bird::move(int speed) {
	int formerAnimationSpriteFrame = animationSpriteFrame;
	setFollowingSpriteFrame();

	birds[animationSpriteFrame].setPosition(birds[formerAnimationSpriteFrame].getPosition());

	if(direction == Left)
		birds[animationSpriteFrame].move(-speed, 0);
	else
		birds[animationSpriteFrame].move(speed, 0);
}

void Bird::setFollowingSpriteFrame() {
	if(animationSpriteFrame < 9)
		animationSpriteFrame++;
	else
		animationSpriteFrame = 0;
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

	target.draw(birds[animationSpriteFrame], states);
}
