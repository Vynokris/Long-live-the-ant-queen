#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


#include "classes.h"



// Upon object creation, set its texture and sprite.
Projectile::Projectile()
{
	texture.loadFromFile("Resources/Art/Attack/Projectile.jpg");
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}


// Spawn the projectile at the player's position and with the right direction.
void Projectile::spawn(sf::Clock& global_clock, float player_position[2], float projectile_direction[2])
{
	spawned = true;

	spawn_time = global_clock.getElapsedTime().asMilliseconds();

	sprite.setPosition(sf::Vector2f(player_position[0], player_position[1]));

	direction[0] = projectile_direction[0];
	direction[1] = projectile_direction[1];
}



// Despawns the projectile.
void Projectile::despawn()
{
	spawned = false;
}



// If the projectile hasn't exceeded its max_lifetime, make it move in function of its direction, then render it onto the game window.
void Projectile::render(sf::Clock& global_clock, sf::RenderWindow& window)
{
	if (global_clock.getElapsedTime().asMilliseconds() - spawn_time <= max_lifetime) {
		// Make the projectile move in function of its direction.
		sprite.setPosition(sf::Vector2f(sprite.getPosition().x + direction[0] * speed, sprite.getPosition().y + direction[1] * speed));

		// Render the projectile onto the game window.
		window.draw(sprite);
	}
	else if (spawned) {
		despawn();
	}
}