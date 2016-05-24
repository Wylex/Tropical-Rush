#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>
#include "TexturesHolder.h"

class MobileCircle: public sf::Drawable {
	private:
		sf::Texture railTexture;
		sf::Texture circleTexture;
		sf::Sprite rail;
		sf::Sprite circle;

		const int maxSpeed = 40;
		const int slowDownZoneSize = 70;
		const int minSpeedPercentage = 10;
		const int msToSlowDown = 10;
		double speed;
		bool isMoving;

		enum {Right, Left} direction;

	public:
		MobileCircle(const TexturesHolder& textures);
		void setIsMoving(bool mv);
		void move();
		void update();
		sf::FloatRect getGlobalBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void setTextures(const TexturesHolder& textures);
		void setInitialPosition();

		bool isInsideBounds() const;
		void fitInsideBounds();
		void changeDirection();
		void keepCircleInsideRail();

		double getSpeedPercentage(double distanceToBorder) const;
		void regulateSpeed();
		void slowDown();
};

#endif
