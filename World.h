#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "MobileCircle.h"
#include "TexturesHolder.h"
#include "Bird.h"

class World {
	private:
		const unsigned int windowXSize = 480;
		const unsigned int windowYSize = 350;

		sf::Sprite background;
		sf::Texture bgTexture;

		sf::RenderWindow window;
		MobileCircle player;
		std::vector<Bird> bird;

		TexturesHolder texturesHolder;

	public:
		World();
		void start();

	private:
		void handleInput();
};

#endif
