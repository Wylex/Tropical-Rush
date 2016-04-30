#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "MobileCircle.h"

class World {
	private:
		const unsigned int windowXSize = 480;
		const unsigned int windowYSize = 350;

		sf::Sprite background;
		sf::Texture bgTexture;

		sf::RenderWindow window;
		MobileCircle player;

	private:
		void handleInput();

	public:
		World();
		void start();
};

#endif
