#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

class MobileCircle: public sf::Drawable {
	private:
		//Rail & Circle
		sf::Sprite rail;
		sf::Texture railTexture;
		sf::Sprite circle;
		sf::Texture circleTexture;

		const int maxSpeed = 50;
		int speed;
		bool isMoving;

		enum {Right, Left} direction;

	/*private:
		void slowDown(int drop);*/

	public:
		MobileCircle();
		void setIsMoving(bool mv);
		void move();
		void update();
		sf::FloatRect getGlobalBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif