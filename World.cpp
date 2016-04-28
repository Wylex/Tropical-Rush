#include "World.h"

World::World(): window{{windowXSize, windowYSize}, "Tropical Rush"} {

}

void World::start() {
	while(window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}
}
