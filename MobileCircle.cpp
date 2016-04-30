#include "MobileCircle.h"
#include <iostream>

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
	speed = maxSpeed;
	direction = Right;
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

void MobileCircle::move() {
	if(direction == Right)
		circle.move(speed/10.0, 0);
	else
		circle.move(-speed/10.0, 0);

	matchBounds();
}

void MobileCircle::update() {
	sf::FloatRect circlePosition = circle.getGlobalBounds();
	sf::FloatRect railPosition = rail.getGlobalBounds();
	int slowDownZoneSize = 70;
	int minSpeedPercentage = 5;

	/*
		|-----|---------------|-----|
		5%   100%
	*/

	//Regulate speed when getting close to borders
	if(isMoving) {
		std::cout << "---" << std::endl;
		if((circlePosition.left - railPosition.left) < slowDownZoneSize) {
			double speedPercentage = (circlePosition.left - railPosition.left) * (100 - minSpeedPercentage) / slowDownZoneSize + minSpeedPercentage;
			speedPercentage /= 100.0;

			speed = speedPercentage * maxSpeed;

			//std::cout << "---" << std::endl;
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

	//Slow down if not moving
	/*if(!isMoving and speed != 0) {
		speed -= maxSpeed/50.0;
		if(speed < 0)
			speed = 0;
	}*/
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
