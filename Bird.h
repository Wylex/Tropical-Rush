#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "TexturesHolder.h"

class Bird: public sf::Drawable {
	public:
		enum Direction {Left, Right};

	private:
		std::vector<sf::Sprite> birds;
		std::vector<sf::Sprite> projectiles;

		int animationSpriteFrame;
		Direction direction;

		//To check if the bird and projectiles are out of the scene
		sf::FloatRect goThroughArea;
		sf::FloatRect windowArea;

	public:
		Bird(const TexturesHolder& textureHolder, Direction direction);
		void move(int speed);
		void shoot();
		bool isVisible() const;
		std::vector<sf::FloatRect> getProjectileBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void buildBird(const TexturesHolder& textureHolder);
		void setSpriteNumber(int numFrames);
		void setBirdTextures(const TexturesHolder& textures, int numFrames);
		void setBirdInitialPosition();

		void setFollowingSpriteFrame();
		bool hasBirdCrossedArea() const;
		bool areProjectilesOutOfScene() const;

};

#endif
