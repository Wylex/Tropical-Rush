#ifndef BIRDREGULATOR_H
#define BIRDREGULATOR_H

#include <vector>
#include <memory>
#include "Bird.h"

typedef std::vector<std::shared_ptr<Bird>>* birds_ptr;

class BirdRegulator{
	private:
		birds_ptr birds;
		const TexturesHolder* textures;

	public:
		BirdRegulator(const TexturesHolder& texturesArg, birds_ptr birdsArg);
		void removeBirdsOutOfScene();
		void spawnBird();
		void moveBirds();
		void updateBirds();
};

#endif
