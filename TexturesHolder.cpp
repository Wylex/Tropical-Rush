#include "TexturesHolder.h"

void TexturesHolder::loadOneFrame(Identifier id, const std::string& filename) {
	std::vector<Texture_ptr> texturesArg;
	texturesArg.push_back(load(filename));

	insertResource(id, texturesArg);
}

void TexturesHolder::loadSeveralFrames(Identifier id, const std::string& filename, int numFrames) {
	std::vector<Texture_ptr> texturesArg;
	for(int i(1); i <= numFrames; i++) {
		std::string path = filename + std::to_string(i) + ".png";
		texturesArg.push_back(load(path));
	}

	insertResource(id, texturesArg);
}

Texture_ptr TexturesHolder::load(std::string filepath) {
	std::shared_ptr<sf::Texture> resource(new sf::Texture());
	resource->loadFromFile(filepath);

	return resource;
}

void TexturesHolder::insertResource(Identifier id, std::vector<Texture_ptr> resource) {
	textures.insert(std::make_pair(id, resource));
}

std::vector<Texture_ptr>& TexturesHolder::get(Identifier id) {
	auto found = textures.find(id);
	return found->second;
}

const std::vector<Texture_ptr>& TexturesHolder::get(Identifier id) const {
	auto found = textures.find(id);
	return found->second;
}
