#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Bird: public sf::Drawable {
	public:
		enum Direction {Left, Right};

	private:
		sf::Texture birdTexture;
		sf::Sprite bird;

		sf::Texture projectileTexture;
		std::vector<sf::Sprite> projectiles;
		sf::FloatRect goThroughArea;
		Direction direction;

		const sf::FloatRect windowArea;

	private:
		bool hasBirdCrossedArea() const;
		bool areProjectilesOutOfScene() const;

	public:
		Bird(sf::FloatRect goThroughArea, Direction direction);
		void move(int speed);
		void shoot();
		bool isVisible() const;
		std::vector<sf::FloatRect> getProjectileBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
