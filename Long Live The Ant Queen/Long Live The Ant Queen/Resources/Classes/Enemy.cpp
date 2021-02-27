#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


#include "classes.h"



// Upon object creation, do nothing.
Enemy::Enemy() {}



// Set the enemy's hp and weapon based on the level argument.
void Enemy::spawn(int lv, float x, float y)
{
	// 1+lv/10 <= hp <= 4+lv/10
	hp = rand() % 4 + 1 + int(lv/10); // I convert lv/10 to int so that I get the quotient of the euclidean division of lv by 10. This means that whenever lv goes up by 10, int(lv/10) goes up by 1.
	
	// Randomly select the enemy's weapon. The higher the wave level, the higher the chance that the enemy has a long range attack. After wave 50, all enemies have a 1/2 chance to be long range.
	if (lv < 50) {
		if (rand() % (100/lv) == 0) {
			weapon = 1;
		}
	}
	else {
		if (rand() % 2 == 0) {
			weapon = 1;
		}
	}

	// Set the enemy's position to the x and y arguments.
	position[0] = x;
	position[1] = y;

	// Reset the enemy's focus.
	if (rand() % 15 == 0) {
		player_focus = true;
	}
	else {
		player_focus = false;
	}

	std::cout << "Enemy spawned at coordinates: x=" << x << " y=" << y << "\n";
}



// Makes the enemy move towards its focus until close enough to attack.
void Enemy::move_logic(sf::Clock& global_clock, float focus_pos[2])
{
	if (hp > 0) {
		// Make it so the enemy faces towards the focused object.
		if (focus_pos[1] <= position[1] + 8 * 5 and sqrt(pow(focus_pos[1] - (position[1] + 8 * 5), 2)) > sqrt(pow(focus_pos[0] - (position[0] + 8 * 5), 2))) {
			// If the focus is above the enemy, and the y distance between the enemy and the focus is superior to the x distance between the enemy and the focus.
			facing = 'N';
		}
		else if (sqrt(pow(focus_pos[1] - (position[1] + 8 * 5), 2)) > sqrt(pow(focus_pos[0] - (position[0] + 8 * 5), 2))) {
			// If the focus is below the enemy, and the y distance between the enemy and the focus is superior to the x distance between the enemy and the focus.
			facing = 'S';
		}
		else if (focus_pos[0] <= position[0] + 8 * 5) {
			// If the focus is to the enemy's left, and the y distance between the enemy and the focus is inferior to the x distance between the enemy and the focus.
			facing = 'W';
		}
		else {
			// If the focus is to the enemy's right, and the y distance between the enemy and the focus is inferior to the x distance between the enemy and the focus.
			facing = 'E';
		}


		// Define distance between the enemy and its focus.
		float distance = float(sqrt(pow(focus_pos[0] - (position[0] + 8 * 5), 2) + pow(focus_pos[1] - (position[1] + 8 * 5), 2)));
		float x_distance = float(sqrt(pow(focus_pos[0] - (position[0] + 8 * 5), 2)));
		float y_distance = float(sqrt(pow(focus_pos[1] - (position[1] + 8 * 5), 2)));


		// Make the enemy move towards its focus if it is far away.
		if ((weapon == 0 and distance >= 110) or (weapon == 1 and distance >= 400)) {
			float temp_direction[2] = { 0.0, 1.0 };
			// The two following operations are based on the unit circle. I make the distance between the enemy and the focus its radius. 
			// Then when I bring the radius back to 1, by proportionnality, I get the x and y distances that would correspond to cos(alpha) and sin(alpha). These are used as the direction.
			temp_direction[0] = float((abs(focus_pos[0] - (position[0] + 8 * 5))) / sqrt(pow((focus_pos[0] - (position[0] + 8 * 5)), 2) + pow(focus_pos[1] - (position[1] + 8 * 5), 2)));
			temp_direction[1] = float((abs(focus_pos[1] - (position[1] + 8 * 5))) / sqrt(pow((focus_pos[0] - (position[0] + 8 * 5)), 2) + pow(focus_pos[1] - (position[1] + 8 * 5), 2)));
			// The next conditions are used to prevent the enemy from always having a positive direction, which would invariably make it go South-East.
			if (focus_pos[0] < position[0] + 8 * 5) {
				temp_direction[0] *= -1;
			}
			if (focus_pos[1] < position[1] + 8 * 5) {
				temp_direction[1] *= -1;
			}

			position[0] += temp_direction[0] * speed;
			position[1] += temp_direction[1] * speed;

			// Prevent the enemy from attacking directily when he is in contact with its focus.
			last_A_time = global_clock.getElapsedTime().asMilliseconds() - 301;
		}

		// Make the enemy align to its focus on one axis if it is close enough and if it has a close range weapon.
		else if (weapon == 0) {
			// If the enemy is closer to its focus on the x axis than on the y axis...
			if (x_distance <= y_distance and x_distance >= speed) {
				// Align to the focus on the x axis.
				if (focus_pos[0] > position[0] + 8 * 5) {
					position[0] += speed;
				}
				else if (focus_pos[0] < position[0] + 8 * 5) {
					position[0] -= speed;
				}
			}
			// If the enemy is closer to its focus on the y axis than on the x axis...
			else if (y_distance <= x_distance and y_distance >= speed) {
				// Align to the focus on the y axis.
				if (focus_pos[1] > position[1] + 8 * 5) {
					position[1] += speed;
				}
				else if (focus_pos[1] < position[1] + 8 * 5) {
					position[1] -= speed;
				}
			}

			// Attack the focus.
			attack_logic(global_clock, focus_pos);
		}
		
		// Make the enemy shoot projectiles if close enough.
		else {
			attack_logic(global_clock, focus_pos);
		}
	}
}



// Makes the enemy attack in function of the distance to its focus and according to a cooldown.
void Enemy::attack_logic(sf::Clock& global_clock, float focus_pos[2])
{
	if (weapon == 0) { // Close range attack.
		if (global_clock.getElapsedTime().asMilliseconds() - last_A_time >= 1000) { // Don't attack if the cooldown isn't done. (Cooldown = 1 second)
			last_A_time = global_clock.getElapsedTime().asMilliseconds(); // Update last_A_time to know when to stop showing the attack animation and when the enemy is able to attack again.
		}
	}
	else if (weapon == 1) { // Long range attack.
		if (global_clock.getElapsedTime().asMilliseconds() - last_A_time >= 2000) { // Don't attack if the cooldown isn't done. (Cooldown = 2 seconds)
			last_A_time = global_clock.getElapsedTime().asMilliseconds(); // Update last_A_time to know when the enemy is able to attack again.
			float temp_direction[2] = { 0.0, 1.0 };
			// The two following operations are based on the unit circle. I make the distance between the enemy and the focus its radius. 
			// Then when I bring the radius back to 1, by proportionnality, I get the x and y distances that would correspond to cos(alpha) and sin(alpha). These are used as the direction.
			temp_direction[0] = float((abs(focus_pos[0] - (position[0] + 8 * 5))) / sqrt(pow((focus_pos[0] - (position[0] + 8 * 5)), 2) + pow(focus_pos[1] - (position[1] + 8 * 5), 2)));
			temp_direction[1] = float((abs(focus_pos[1] - (position[1] + 8 * 5))) / sqrt(pow((focus_pos[0] - (position[0] + 8 * 5)), 2) + pow(focus_pos[1] - (position[1] + 8 * 5), 2)));
			// The next conditions are used to prevent the enemy from always having a positive direction, which would invariably make it go South-East.
			if (focus_pos[0] < position[0] + 8 * 5) {
				temp_direction[0] *= -1;
			}
			if (focus_pos[1] < position[1] + 8 * 5) {
				temp_direction[1] *= -1;
			}
			// Spawn the projectile.
			projectile.spawn(global_clock, position, temp_direction);
		}
	}
}



// Enables the enemy to take damage from the player.
void Enemy::damage_logic(sf::Clock& global_clock, Player& player)
{
	if (hp > 0)
	{
		// If the player is currently attacking...
		if ((not taken_damage) and global_clock.getElapsedTime().asMilliseconds() - player.last_A_time <= player.A_speed[2])
		{
			// If the enemy is in range of the player's attack... (meaning if the enemy's sprite and the player's attack sprite overlap)
			if (sprite.getGlobalBounds().intersects(player.A_sprite.getGlobalBounds()))
			{
				hp -= 1;

				// Add 1 to the player's kill count if the enemy is dead.
				if (hp == 0 and not taken_damage) {
					player.kills++;
					player.kills_in_current_wave++;
				}

				taken_damage = true;

				// 1 in 2 chance to change his focus to the player.
				if ((not player_focus) and rand() % 2 == 0) { 
					player_focus = true;
				}
			}
		}
		// If the player isn't attacking anymore...
		else if (taken_damage and global_clock.getElapsedTime().asMilliseconds() - player.last_A_time > player.A_speed[2])
		{
			// Reset the taken_damage variable if the player's attack is finished.
			taken_damage = false;
		}

	
		// Check collision with projectiles. Take tamage if their sprites overlap.
		for (int i = 0; i < 2; i++) {
			if (sprite.getGlobalBounds().intersects(player.projectile[i].sprite.getGlobalBounds()) and player.projectile[i].spawned) 
			{
				player.projectile[i].despawn();

				hp -= 1;

				// Add 1 to the player's kill count if the enemy is dead.
				if (hp == 0) {
					player.kills++;
					player.kills_in_current_wave++;
				}

				// 1 in 4 chance to change his focus to the player.
				if ((not player_focus) and rand() % 4 == 0) { 
					player_focus = true;
				}
			}
		}
	}
}



// Makes the enemy disappear and potentially drop something if its hp is at 0. Useless for now because the enemies don't drop anything.
void Enemy::kill()
{
	
}



// Renders the enemy's current sprite onto the game window.
void Enemy::render(sf::RenderWindow& window)
{
	if (hp > 0) {
		// Create the enemy's texture and make its name the direction the player is facing.
		std::string texture_name = "Resources/Art/Enemy/";
		texture_name += facing;
		texture_name += ".png";
		texture.loadFromFile(texture_name);

		// Load the texture onto the enemy's sprite.
		sprite.setTexture(texture);
		sprite.setScale(scale, scale);
		sprite.setPosition(sf::Vector2f(position[0], position[1]));

		// Render the texture on the window.
		window.draw(sprite);
	}
}



// Renders the enemy's attack sprite onto the game window.
void Enemy::render_attack(sf::Clock& global_clock, sf::RenderWindow& window)
{
	if (hp > 0)
	{
		// If the enemy has a close range weapon.
		if (weapon == 0) 
		{
			// Move the enemy's attack sprite.
			if (facing == 'N') {
				A_sprite.setPosition(sf::Vector2f(position[0], position[1] - A_sprite.getTextureRect().height * scale));
			}
			else if (facing == 'S') {
				A_sprite.setPosition(sf::Vector2f(position[0], position[1] + A_sprite.getTextureRect().height * scale));
			}
			else if (facing == 'W') {
				A_sprite.setPosition(sf::Vector2f(position[0] - A_sprite.getTextureRect().width * scale, position[1]));
			}
			else if (facing == 'E') {
				A_sprite.setPosition(sf::Vector2f(position[0] + A_sprite.getTextureRect().width * scale, position[1]));
			}

			// Render the enemy's attack if he is attacking.
			if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= 300)
			{
				// Create the enemy's attack texture and make its name "Resources/Art/Attack/facing_int.jpg", with int a number between 0 and 2 to animate the attack.
				std::string A_texture_name = "Resources/Art/Attack/";
				A_texture_name += facing;

				if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= 100) {
					// First frame of the attack animation.
					A_texture_name += "_0";
				}
				else if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= 200) {
					// Second frame of the attack animation.
					A_texture_name += "_1";
				}
				else {
					// Last frame of the attack animation.
					A_texture_name += "_2";
				}

				A_texture_name += ".jpg"; // Temporary art is .jpg, final will probably be .png.

				if (A_texture_name == current_A_texture_name) {
					// If the player's attack sprite and texture haven't changed since last frame, only render the attack sprite onto the game window.
					window.draw(A_sprite);
				}
				else {
					// Load the texture onto the player's sprite.
					A_texture.loadFromFile(A_texture_name);
					A_sprite.setTexture(A_texture);
					A_sprite.setScale(scale, scale);

					// Render the sprite of the player's attack on the window.
					window.draw(A_sprite);

					// Update the current_A_texture_name variable.
					current_A_texture_name = A_texture_name;
				}
			}
		}
	}
}



// Render the sprite of the enemy's projectiles onto the game window.
void Enemy::render_projectiles(sf::Clock& global_clock, sf::RenderWindow& window)
{
	if (hp > 0)
	{
		// If the enemy has a long range weapon.
		if (weapon == 1) {
			if (projectile.spawned) {
				projectile.render(global_clock, window);
			}
		}
	}
}




// Reset the enemy object.
void Enemy::reset()
{
	last_A_time = -1;

	facing = 'S';
	position[0] = 0.0;
	position[1] = 0.0;
	scale = 5.0;
	speed = 0.5;

	hp = 0;
	weapon = 0;
	player_focus = false;
	taken_damage = false;
	damaged_queen = false;
	damaged_player = false;
}