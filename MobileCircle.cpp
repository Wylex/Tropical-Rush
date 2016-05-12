#include "MobileCircle.h"

MobileCircle::MobileCircle() {
	//Rail and Circle
	railTexture.loadFromFile("Resources/rail.png");
	rail.setTexture(railTexture);
	circleTexture.loadFromFile("Resources/circle.png");
	circle.setTexture(circleTexture);

	//Set position
	const int verticalPosition = 290;
	const int horizontalPosition = 30;
	rail.setPosition(horizontalPosition, verticalPosition);
	circle.setPosition(horizontalPosition + rail.getGlobalBounds().width/2 - circle.getGlobalBounds().width/2, verticalPosition - 8);

	//Initialize variables
	isMoving = false;
	speed = 0;
	direction = Right;
}

bool MobileCircle::isInsideBounds() const {
	double circleRightCoordinate = circle.getGlobalBounds().left + circle.getGlobalBounds().width;
	double railRightCoordinate = rail.getGlobalBounds().left + rail.getGlobalBounds().width;

	bool insideBounds = true;

	if(circleRightCoordinate > railRightCoordinate)
		insideBounds = false;
	else if(circle.getGlobalBounds().left < rail.getGlobalBounds().left)
		insideBounds = false;

	return insideBounds;
}

void MobileCircle::fitInsideBounds() {
	double circleRightCoordinate = circle.getGlobalBounds().left + circle.getGlobalBounds().width;
	double railRightCoordinate = rail.getGlobalBounds().left + rail.getGlobalBounds().width;

	if(circleRightCoordinate > railRightCoordinate)
		circle.setPosition(railRightCoordinate - circle.getGlobalBounds().width, circle.getGlobalBounds().top);
	else if(circle.getGlobalBounds().left < rail.getGlobalBounds().left)
		circle.setPosition(rail.getGlobalBounds().left, circle.getGlobalBounds().top);
}

void MobileCircle::changeDirection() {
	if(direction == Left)
		direction = Right;
	else
		direction = Left;
}

void MobileCircle::keepCircleInsideRail() {
	if(!isInsideBounds()) {
		fitInsideBounds();
		changeDirection();
	}
}

void MobileCircle::move() {
	if(direction == Right)
		circle.move(speed/10.0, 0);
	else
		circle.move(-speed/10.0, 0);

	keepCircleInsideRail();
}

double MobileCircle::getSpeedPercentage(double distanceToBorder) const {
	//Percentage from 0 to (100 - minSpeedPercentage) and then
	//addition of minSpeedPercentage to avoid 0% speed
	double speedPercentage = distanceToBorder * (100 - minSpeedPercentage) / slowDownZoneSize;
	speedPercentage += minSpeedPercentage;

	return speedPercentage/100.0;
}

void MobileCircle::regulateSpeed() {
	sf::FloatRect circlePosition = circle.getGlobalBounds();
	sf::FloatRect railPosition = rail.getGlobalBounds();

	double circleRightCoordinate = circlePosition.left + circlePosition.width;
	double railRightCoordinate = railPosition.left + railPosition.width;

	//Slow down when getting close to borders
	if((circlePosition.left - railPosition.left) < slowDownZoneSize) {
		double distanceToBorder = circlePosition.left - railPosition.left;
		speed = getSpeedPercentage(distanceToBorder) * maxSpeed;
	}
	else if(circleRightCoordinate > railRightCoordinate - slowDownZoneSize) {
		double distanceToBorder = railRightCoordinate - circleRightCoordinate;
		speed = getSpeedPercentage(distanceToBorder) * maxSpeed;
	}
	//Max speed in the middle of the rail
	else
		speed = maxSpeed;
}

void MobileCircle::slowDown() {
	speed *= 0.95;
	if(speed < 1)
		speed = 0;
}

void MobileCircle::update() {
	//Regulate speed while moving
	if(isMoving)
		regulateSpeed();

	//Slow down if not moving (and keep moving)
	static sf::Clock timeSinceLastDecrease;
	if(!isMoving and speed != 0 and timeSinceLastDecrease.getElapsedTime().asMilliseconds() > msToSlowDown) {
		slowDown();
		move();
		timeSinceLastDecrease.restart();
	}
}

void MobileCircle::setIsMoving(bool mv) {
	isMoving = mv;
}

sf::FloatRect MobileCircle::getGlobalBounds() const {
	return circle.getGlobalBounds();
}

void MobileCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rail, states);
	target.draw(circle, states);
}
