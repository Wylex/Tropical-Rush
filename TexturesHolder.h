#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map>
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

typedef std::shared_ptr<sf::Texture> Texture_ptr;

class TexturesHolder {
	public:
		enum Identifier {BirdRight, BirdLeft, Projectile, Rail, Circle, Background};
	private:
		std::map<Identifier, std::vector<Texture_ptr>> textures;

	public:
		void loadOneFrame(Identifier id, const std::string& filename);
		void loadSeveralFrames(Identifier id, const std::string& filename, int numFrames);

		std::vector<Texture_ptr>& get(Identifier id);
		const std::vector<Texture_ptr>& get(Identifier id) const;

	private:
		void insertResource(Identifier id, std::vector<Texture_ptr> resource);
		Texture_ptr load(std::string filepath);
};

#endif
