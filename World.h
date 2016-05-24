#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "MobileCircle.h"
#include "Bird.h"
#include "BirdRegulator.h"
#include "TexturesHolder.h"

class World {
	private:
		const unsigned int windowXSize = 480;
		const unsigned int windowYSize = 350;

		sf::Sprite background;
		//sf::Texture bgTexture;

		sf::RenderWindow window;
		MobileCircle player;

		std::vector<std::shared_ptr<Bird>> birds;
		BirdRegulator birdRegulator;

		TexturesHolder texturesHolder;

	public:
		World();
		void start();

	private:
		void handleInput();
		void loadTextures();
};

#endif
