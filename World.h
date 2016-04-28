#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

class World {
	private:
		const unsigned int windowXSize = 480;
		const unsigned int windowYSize = 350;

		sf::RenderWindow window;

	public:
		World();
		void start();
};

#endif
