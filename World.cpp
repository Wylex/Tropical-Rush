#include "World.h"
#include <iostream>

World::World(): window{{windowXSize, windowYSize}, "Tropical Rush"} {
	bgTexture.loadFromFile("Resources/background.png");
	background.setTexture(bgTexture);

	texturesHolder.loadSeveralFrames(TexturesHolder::BirdLeft, "Resources/Bird/birdanimationL", 10);
	texturesHolder.loadSeveralFrames(TexturesHolder::BirdRight, "Resources/Bird/birdanimationR", 10);

	bird.push_back(Bird(texturesHolder, Bird::Direction::Right));
}

void World::start() {
	while(window.isOpen()) {

		handleInput();

		player.update();

		window.clear();
		window.draw(background);
		window.draw(player);
		window.display();
	}
}

void World::handleInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space)
					player.setIsMoving(true);
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Space)
					player.setIsMoving(false);
				break;
		}
	}

	static sf::Clock timeSinceLastMove;
	if(timeSinceLastMove.getElapsedTime().asMilliseconds() > 20) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			player.move();
			timeSinceLastMove.restart();
		}
	}

}
