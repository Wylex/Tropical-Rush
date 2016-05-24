#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "TexturesHolder.h"
#include "Projectile.h"

class Bird: public sf::Drawable {
	public:
		enum Direction {Left, Right};

	private:
		std::vector<sf::Sprite> birds;
		std::vector<Projectile> projectiles;
		const TexturesHolder* textures;

		int animationSpriteFrame;
		Direction direction;

		//To check if the bird and projectiles are out of the scene
		sf::FloatRect goThroughArea;
		sf::FloatRect windowArea;

	public:
		Bird(const TexturesHolder& textureHolder, Direction direction);
		void move(double speed);
		void shoot();
		void updateProjectilesPosition();
		bool isVisible() const;
		std::vector<sf::FloatRect> getProjectileBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void buildBird();
		void setSpriteNumber(int numFrames);
		void setBirdTextures(int numFrames);
		void setBirdInitialPosition();

		void setFollowingSpriteFrame();
		bool hasBirdCrossedArea() const;
		bool areProjectilesOutOfScene() const;

};

#endif
