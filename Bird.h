#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Bird: public sf::Drawable {
	private:
		sf::Texture birdTexture;
		sf::Sprite bird;

		sf::Texture projectileTexture;
		std::vector<sf::Sprite> projectiles;

	public:
		enum Direction {Left, Right} direction;

		Bird(sf::FloatRect goThroughArea, Direction direction);
		void move(int speed);
		void shoot();
		std::vector<sf::FloatRect> getGlobalBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
