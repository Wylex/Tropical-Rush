#include "MobileCircle.h"

MobileCircle::MobileCircle() {
	//Rail
	railTexture.loadFromFile("Resources/rail.png");
	rail.setTexture(railTexture);
	//Circle
	circleTexture.loadFromFile("Resources/circle.png");
	circle.setTexture(circleTexture);

	const int verticalPosition = 290;
	const int horizontalPosition = 30;
	rail.setPosition(horizontalPosition, verticalPosition);
	circle.setPosition(horizontalPosition + rail.getGlobalBounds().width/2 - circle.getGlobalBounds().width/2, verticalPosition - 8);

	isMoving = false;
	speed = 0;
	direction = Right;
}

void MobileCircle::move() {
	if(direction == Right)
		circle.move(speed/10.0, 0);
	else
		circle.move(-speed/10.0, 0);

	matchBounds();
}

void MobileCircle::regulateSpeed() {
	sf::FloatRect circlePosition = circle.getGlobalBounds();
	sf::FloatRect railPosition = rail.getGlobalBounds();

	//Slow down when getting close to borders
	if((circlePosition.left - railPosition.left) < slowDownZoneSize) {
		double speedPercentage = (circlePosition.left - railPosition.left) * (100 - minSpeedPercentage) / slowDownZoneSize + minSpeedPercentage;
		speedPercentage /= 100.0;

		speed = speedPercentage * maxSpeed;
	}
	else if(circlePosition.left + circlePosition.width > (railPosition.left + railPosition.width) - slowDownZoneSize) {
		double speedPercentage = (railPosition.left + railPosition.width) - (circlePosition.left + circlePosition.width);
		speedPercentage = speedPercentage * (100 - minSpeedPercentage) / slowDownZoneSize + minSpeedPercentage;
		speedPercentage /= 100.0;

		speed = speedPercentage * maxSpeed;
	}
	else
		speed = maxSpeed;
}

void MobileCircle::slowDown() {
	speed -= maxSpeed/20.0;
	if(speed < 0)
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

void MobileCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rail, states);
	target.draw(circle, states);
}

void MobileCircle::setIsMoving(bool mv) {
	isMoving = mv;
}

sf::FloatRect MobileCircle::getGlobalBounds() const {
	return circle.getGlobalBounds();
}

void MobileCircle::matchBounds() {
	if(circle.getGlobalBounds().left + circle.getGlobalBounds().width > rail.getGlobalBounds().left + rail.getGlobalBounds().width) {
		direction = Left;
		circle.setPosition(rail.getGlobalBounds().left + rail.getGlobalBounds().width - circle.getGlobalBounds().width, circle.getGlobalBounds().top);
	}
	else if(circle.getGlobalBounds().left < rail.getGlobalBounds().left) {
		direction = Right;
		circle.setPosition(rail.getGlobalBounds().left, circle.getGlobalBounds().top);
	}
}
