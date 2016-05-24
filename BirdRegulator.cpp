#include "BirdRegulator.h"
#include <ctime>
#include <cstdlib>

BirdRegulator::BirdRegulator(const TexturesHolder& texturesArg, birds_ptr birdsArg): textures(&texturesArg) {
	std::srand(time(NULL));

	birds = birdsArg;
}

void BirdRegulator::removeBirdsOutOfScene() {
	for(int i(birds->size()-1); i >= 0; i--) {
		std::shared_ptr<Bird> bird_ptr = (*birds)[i];
		if(!bird_ptr->isVisible()) {
			birds->pop_back();
		}
	}
}

void BirdRegulator::spawnBird() {
	int rdm = std::rand()%2;
	if(rdm = 0)
		birds->push_back(std::shared_ptr<Bird>(new Bird(*textures, Bird::Left)));
	else
		birds->push_back(std::shared_ptr<Bird>(new Bird(*textures, Bird::Right)));
}

void BirdRegulator::moveBirds() {
	const double speed{0.2};

	for(int i(0); i < birds->size(); i++)
		(*birds)[i]->move(speed);
}

void BirdRegulator::updateBirds() {
	for(int i(0); i < birds->size(); i++)
		(*birds)[i]->updateProjectilesPosition();
}
