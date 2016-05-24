#include "World.h"
#include <iostream>

World::World(): window{{windowXSize, windowYSize}, "Tropical Rush"}, birdRegulator(texturesHolder, &birds), player(texturesHolder) {
	loadTextures();
	//bgTexture.loadFromFile("Resources/background.png");
	std::vector<std::shared_ptr<sf::Texture>> texture_ptr = texturesHolder.get(TexturesHolder::Background);

	background.setTexture(*(texture_ptr[0]));

	birdRegulator.spawnBird();
}

void World::loadTextures() {
	texturesHolder.loadSeveralFrames(TexturesHolder::BirdLeft, "Resources/Bird/birdanimationL", 10);
	texturesHolder.loadSeveralFrames(TexturesHolder::BirdRight, "Resources/Bird/birdanimationR", 10);
	texturesHolder.loadOneFrame(TexturesHolder::Rail, "Resources/rail.png");
	texturesHolder.loadOneFrame(TexturesHolder::Circle, "Resources/circle.png");
	texturesHolder.loadOneFrame(TexturesHolder::Background, "Resources/background.png");
	texturesHolder.loadOneFrame(TexturesHolder::Projectile, "Resources/projectile.png");
}

void World::start() {
	while(window.isOpen()) {

		handleInput();

		player.update();

		static sf::Clock aa;
		if(aa.getElapsedTime().asMilliseconds() > 20) {
			birdRegulator.moveBirds();
			aa.restart();
		}


		birdRegulator.removeBirdsOutOfScene();

		window.clear();
		window.draw(background);
		window.draw(*(birds[0]));
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
