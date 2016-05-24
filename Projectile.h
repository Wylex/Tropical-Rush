#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "TexturesHolder.h"

class Projectile: public sf::Drawable {
	private:
		sf::Sprite projectile;

	public:
		Projectile(const TexturesHolder& textures, sf::Vector2f position);
		void move(sf::Vector2f velocity);
		sf::FloatRect getGlobalBounds() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void setTexture(const TexturesHolder& textures);
};

#endif
