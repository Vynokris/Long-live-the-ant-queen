#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


#include "classes.h"



// Upon object creation, set its texture and sprite.
Queen::Queen()
{
	texture.loadFromFile("Resources/Art/Queen/Queen.png");
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}



// Enables the queen to take damage from the enemies.
void Queen::damage_logic(sf::Clock& global_clock, Enemy& enemy)
{
	if (hp > 0)
	{
		// If the enemy has a close range weapon.
		if (enemy.weapon == 0) {
			// If the enemy is currently attacking... (assuming the attak animation is 300 milliseconds long)
			if ((not enemy.damaged_queen) and global_clock.getElapsedTime().asMilliseconds() - enemy.last_A_time <= 300)
			{
				// If the queen is in range of the enemy's attack... (meaning if the queen's sprite and the enemy's attack sprite overlap)
				if (sprite.getGlobalBounds().intersects(enemy.A_sprite.getGlobalBounds()))
				{
					hp -= 1;
					enemy.damaged_queen = true;
				}
			}
			// If the enemy isn't attacking anymore...
			else if (enemy.damaged_queen and global_clock.getElapsedTime().asMilliseconds() - enemy.last_A_time > 300)
			{
				// Reset the taken_damage variable if the enemy's attack is finished.
				enemy.damaged_queen = false;
			}
		}

		// If the enemy has a long range weapon.
		else if (enemy.weapon == 1) {
			// Check collision with projectiles. Take tamage if their sprites overlap.
			for (int i = 0; i < 2; i++) {
				if (sprite.getGlobalBounds().intersects(enemy.projectile.sprite.getGlobalBounds()) and enemy.projectile.spawned) {
					enemy.projectile.despawn();
					hp -= 1;
				}
			}
		}
	}
}



// Renders the queen's sprite onto the game window.
void Queen::render(sf::RenderWindow& window)
{
	if (hp > 0)
	{
		sprite.setPosition(float(position[0] - sprite.getTextureRect().width * scale / 2), float(position[1] - sprite.getTextureRect().height * scale / 2));
		window.draw(sprite);
	}
}



// Reset the queen object.
void Queen::reset()
{
	position[0] = 960.0;
	position[1] = 500.0;
	scale = 5.0;
	hp = 5;
	taken_damage = false;
}