#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

class MobileCircle: public sf::Drawable {
	private:
		sf::Sprite rail;
		sf::Texture railTexture;
		sf::Sprite circle;
		sf::Texture circleTexture;

		const int maxSpeed = 40;
		const int slowDownZoneSize = 70;
		const int minSpeedPercentage = 10;
		const int msToSlowDown = 10;
		double speed;
		bool isMoving;

		enum {Right, Left} direction;

	public:
		MobileCircle();
		void setIsMoving(bool mv);
		void move();
		void update();
		sf::FloatRect getGlobalBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		bool isInsideBounds() const;
		void fitInsideBounds();
		void changeDirection();
		void keepCircleInsideRail();

		double getSpeedPercentage(double distanceToBorder) const;
		void regulateSpeed();
		void slowDown();
};

#endif
