#include "Projectile.h"

Projectile::Projectile(const TexturesHolder& textures, sf::Vector2f position) {
	setTexture(textures);
	projectile.setPosition(position);
}

void Projectile::setTexture(const TexturesHolder& textures) {
	auto textures_ptr = textures.get(TexturesHolder::Projectile);
	std::shared_ptr<sf::Texture> texture_ptr{textures_ptr[0]};

	projectile.setTexture(*texture_ptr);
}

void Projectile::move(sf::Vector2f velocity) {
	projectile.move(velocity);
}

sf::FloatRect Projectile::getGlobalBounds() const {
	return projectile.getGlobalBounds();
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(projectile, states);
}
