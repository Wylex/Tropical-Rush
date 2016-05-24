#include "Bird.h"
#include <ctime>
#include <cstdlib>
#include <string>

Bird::Bird(const TexturesHolder& textureHolder, Direction directionArg): textures(&textureHolder) {

	std::srand(time(NULL));

	direction = directionArg;
	animationSpriteFrame = 0;
	windowArea = sf::FloatRect(0, 0, 480, 350);
	goThroughArea = sf::FloatRect(0, 50, 480, 100);

	buildBird();
}

void Bird::buildBird() {
	const int numberOfFrames = 10;
	setSpriteNumber(numberOfFrames);
	setBirdTextures(numberOfFrames);
	setBirdInitialPosition();
}

void Bird::setSpriteNumber(int numFrames) {
	birds.resize(numFrames);
}

void Bird::setBirdTextures(int numFrames) {
	std::vector<std::shared_ptr<sf::Texture>> textures_ptr;
	if(direction == Left)
		textures_ptr = textures->get(TexturesHolder::BirdLeft);
	else
		textures_ptr = textures->get(TexturesHolder::BirdRight);

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

void Bird::move(double speed) {
	static int numberOfCalls = -1;
	numberOfCalls++;
	int formerAnimationSpriteFrame = animationSpriteFrame;
	if(numberOfCalls >= 10) {
		setFollowingSpriteFrame();
		numberOfCalls = 0;
	}

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

void Bird::updateProjectilesPosition() {
	const sf::Vector2f projectileGravity{0, 0.1};

	for(int i(0); i < projectiles.size(); i++) {
		projectiles[i].move(projectileGravity);
	}
}

void Bird::shoot() {
	sf::Vector2f birdPos = birds[animationSpriteFrame].getPosition();
	projectiles.push_back(Projectile(*textures, birdPos));
}

std::vector<sf::FloatRect> Bird::getProjectileBounds() const {
	std::vector<sf::FloatRect> projectilesBounds;

	for(int i(0); i < projectiles.size(); i++)
		projectilesBounds.push_back(projectiles[i].getGlobalBounds());

	return projectilesBounds;
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//Posible problema para el draw de los projectiles
	for(int i(0); i < projectiles.size(); i++)
		target.draw(projectiles[i]);

	target.draw(birds[animationSpriteFrame], states);
}
