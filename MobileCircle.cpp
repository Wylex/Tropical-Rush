#include "MobileCircle.h"

MobileCircle::MobileCircle() {
	//Rail
	railTexture.loadFromFile("");
	rail.setTexture(railTexture);
	//Circle
	circleTexture.loadFromFile("");
	circle.setTexture(circleTexture);
	circle.setPosition(480/2 - rail.getLocalBounds().width/2, 300);

	isMoving = false;
	speed = maxSpeed;
	direction = Left;
}

void MobileCircle::move() {
	if(direction == Right)
		circle.move(speed/10.0, 0);
	else
		circle.move(-speed/10.0, 0);
}

/*void MobileCircle::slowDown(int drop) {
	if(velocity > 0) {
		velocity -= drop;
		if(velocity < 0)
			velocity = 0;
	}
	else if(velocity < 0) {
		velocity += drop;
		if(velocity > 0)
			velocity = 0;
	}
}*/

void MobileCircle::update() {
	sf::FloatRect circlePosition = circle.getGlobalBounds();
	sf::FloatRect railPosition = rail.getGlobalBounds();
	int slowDownZoneSize = 70;
	int minSpeedPercentage = 5;

	/*
		|-----|---------------------|
		0%   100%
	*/

	//Regulate speed when getting close to borders
	if(isMoving) {
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

	//Slow down if not moving
	if(!isMoving) {
		speed -= 3;
		if(speed < 0)
			speed = 0;
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
