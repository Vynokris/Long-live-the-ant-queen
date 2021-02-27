#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>


#include "classes.h"



// Upon object creation, do nothing (temporary).
Player::Player()
{
	// Does nothing for now
}



// Returns a string of len 4.
// The 1st char is 't' if the player is colliding with the top border of the window, 'f' if not.
// The 2nd is for the bottom.
// The 3rd for the left.
// The 4th for the right.
std::string Player::colliding_with_border()
{
	std::string up_collision = "f";
	std::string down_collision = "f";
	std::string left_collision = "f";
	std::string right_collision = "f";

	// Test collision with the upper part of the window. Currently 75 because there is a wall in the top of the window that the player shouldn't be able to walk on.
	if (position[1] <= 75) {
		up_collision = "t";
	}
	// Test collision with the lower part of the window.
	else if (position[1] >= 1080 - sprite.getTextureRect().height * (scale + 2)) { // I don't know why I have to add 2 to the scale here, but if I don't, the player is able to go half out of the bottom of the window.
		down_collision = "t";
	}
	// Test collision with the left part of the window. Currently -10 because for some reason 0 isn't exactly the left side of the window.
	if (position[0] <= -10) {
		left_collision = "t";
	}
	// Test collision with the right part of the window.
	else if (position[0] >= 1920 - sprite.getTextureRect().width * (scale -1)) { // I don't know why I have to substract 1 to the scale here, but if I don't, the player isn't able to touch the right border of the window.
		right_collision = "t";
	}

	return up_collision + down_collision + left_collision + right_collision;
}



// Processes user input and calls the adequate functions (walk, dash, attack, block, pause).
void Player::input_logic(sf::Clock& global_clock, sf::Keyboard::Key keybindings[6], sf::Mouse::Button mousebindings[2], sf::Vector2i mouse_pos)
{
	// Block with keybindings[5].
	if (sf::Keyboard::isKeyPressed(keybindings[5])) {
		attack(global_clock, 2, mouse_pos);
	}

	// Close range attack with mousebindings[0]. Long range attack with mousebindings[1].
	for (int i = 0; i < 2; i++) {
		if (sf::Mouse::isButtonPressed(mousebindings[i])) {
			attack(global_clock, i, mouse_pos);
		}
	}


	float temp_move[2] = { 0.0, 0.0 };
	// Go up with keybindings[0].
	if (sf::Keyboard::isKeyPressed(keybindings[0]))
	{
		// Make sure the player isn't colliding with the top border of the window.
		if (colliding_with_border()[0] == 'f') {
			temp_move[1] = -1.0;
		}
	}
	// Go down with keybindings[1].
	if (sf::Keyboard::isKeyPressed(keybindings[1]))
	{
		// Make sure the player isn't colliding with the bottom border of the window.
		if (colliding_with_border()[1] == 'f') {
			temp_move[1] = 1.0;
		}
	}
	// Go left with keybindings[2].
	if (sf::Keyboard::isKeyPressed(keybindings[2]))
	{
		// Make sure the player isn't colliding with the left border of the window.
		if (colliding_with_border()[2] == 'f') {
			temp_move[0] = -1.0;
		}
	}
	// Go right with keybindings[3].
	if (sf::Keyboard::isKeyPressed(keybindings[3]))
	{
		// Make sure the player isn't colliding with the right border of the window.
		if (colliding_with_border()[3] == 'f') {
			temp_move[0] = 1.0;
		}
	}
	// Move the player according to the user inputs.
	move(global_clock, temp_move[0], temp_move[1]);


	// Dash with keybindings[0].
	if (sf::Keyboard::isKeyPressed(keybindings[4]))
	{
		dash(global_clock);
	}
}



// Moves the player's sprite in the direction given by x and y. x and y must be either 1, 0 or -1.
void Player::move(sf::Clock& global_clock, float x, float y)
{
	// The next condition is used to make the player have the same speed when moving diagonally, horizontally or vertically.
	// I use a right isosceles triangle of hypotenuse = 1 and determinate the size of its other sides, which I use as x and y values. This means that even when moving diagonally, the player will move of 1 distance unit.
	if (x != 0 and y != 0) {
		x *= float(sqrt(0.5)); // Here I multipy instead of directly assigning the value to not lose the sign of x and y. They can only be equal to 1 or -1 so no problem for the value.
		y *= float(sqrt(0.5)); // Same here.
	}
	
	// Make the player move according to the x, y and speed parameters. If the player is dashing, multiply his speed by dash_speed.
	if (global_clock.getElapsedTime().asMilliseconds() - last_dash_time <= dash_duration and not blocking) {
		position[0] += x * speed * dash_speed;
		position[1] += y * speed * dash_speed;
	}
	else if (not blocking) {
		position[0] += x * speed;
		position[1] += y * speed;
	}
	else {
		position[0] += x * speed / 2;
		position[1] += y * speed / 2;
	}
}



// Makes the player dash by updating the last dash time if the cooldown is finished.
void Player::dash(sf::Clock& global_clock)
{
	// Dash cooldown.
	if (global_clock.getElapsedTime().asMilliseconds() - last_dash_time >= dash_cooldown) {
		last_dash_time = global_clock.getElapsedTime().asMilliseconds();
	}
}



// Makes the player attack (type argument: 0=close attack, 1=ranged attack, 2=block).
void Player::attack(sf::Clock& global_clock, int type, sf::Vector2i mouse_pos)
{
	// Close range attack.
	if (type == 0 and not blocking) // Can't attack if already blocking.
	{ 
		if (global_clock.getElapsedTime().asMilliseconds() - last_A_time >= A_cooldown) // Don't attack if the attack cooldown isn't done.
		{
			last_A_time = global_clock.getElapsedTime().asMilliseconds(); // Update last_A_time to start the attack animation, to know when to stop showing it and to know when the player is able to attack again.
		}
	}

	// Long range attack.
	else if (type == 1 and not blocking) // Can't attack if already blocking.
	{ 
		// Find the direction to shoot the projectile in.
		float temp_direction[2] = { 0.0, 1.0 };
			// The two following operations are based on the unit circle. I make the distance between the player and the pointer its radius. 
			// Then when I bring the radius back to 1, by proportionnality, I get the x and y distances that would correspond to cos(alpha) and sin(alpha). These are used as the direction.
		temp_direction[0] = float((abs(mouse_pos.x - position[0])) / sqrt(pow((mouse_pos.x - position[0]), 2) + pow((mouse_pos.y - position[1]), 2)));
		temp_direction[1] = float((abs(mouse_pos.y - position[1])) / sqrt(pow((mouse_pos.x - position[0]), 2) + pow((mouse_pos.y - position[1]), 2)));
			// The next conditions are used to prevent the projectiles from always having a positive direction, which would invariably make them go South-East.
		if (mouse_pos.x < position[0]) {
			temp_direction[0] *= -1;
		}
		if (mouse_pos.y < position[1]) {
			temp_direction[1] *= -1;
		}

		// Shoot a projectile if it has been spawned long enough ago.
		for (int i = 0; i < 2; i++) {
			if (not projectile[i].spawned and global_clock.getElapsedTime().asMilliseconds() - last_projectile_time >= projectile_cooldown) {
				projectile[i].spawn(global_clock, position, temp_direction);
				last_projectile_time = global_clock.getElapsedTime().asMilliseconds();
			}
		}
	}

	// Block.
	else {
		blocking = true;
		if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= A_cooldown) {
			last_A_time -= A_cooldown;
		}
	}
}



// Enables the player to take damage from the enemies.
void Player::damage_logic(sf::Clock& global_clock, Enemy& enemy)
{
	if (hp > 0 and not blocking)
	{
		// If the enemy has a close range weapon.
		if (enemy.weapon == 0) {
			// If the enemy is currently attacking... (assuming the attak animation is 300 milliseconds long)
			if ((not enemy.damaged_player) and global_clock.getElapsedTime().asMilliseconds() - enemy.last_A_time <= 300)
			{
				// If the player is in range of the enemy's attack... (meaning if the player's sprite and the enemy's attack sprite overlap)
				if (sprite.getGlobalBounds().intersects(enemy.A_sprite.getGlobalBounds()))
				{
					hp -= 1;
					enemy.damaged_player = true;
				}
			}
			// If the enemy isn't attacking anymore...
			else if (enemy.damaged_player and global_clock.getElapsedTime().asMilliseconds() - enemy.last_A_time > 300)
			{
				// Reset the taken_damage variable if the enemy's attack is finished.
				enemy.damaged_player = false;
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



// Renders the player's current sprite onto the game window.
void Player::render(sf::RenderWindow &window)
{
	// Make the character face the mouse pointer.
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	if (mouse_pos.y <= position[1] + 16 * 5 and abs(position[1] - mouse_pos.y) > abs(position[0] - mouse_pos.x)) {
		// If the mouse is above the player, and the y distance between the player and the mouse is superior to the x distance between the player and the mouse.
		facing = 'N';
	}
	else if (abs(position[1] - mouse_pos.y) > abs(position[0] - mouse_pos.x)) {
		// If the mouse is below the player, and the y distance between the player and the mouse is superior to the x distance between the player and the mouse.
		facing = 'S';
	}
	else if (mouse_pos.x <= position[0] + 8 * 5) {
		// If the mouse is to the player's left, and the y distance between the player and the mouse is inferior to the x distance between the player and the mouse.
		facing = 'W';
	}
	else {
		// If the mouse is to the player's right, and the y distance between the player and the mouse is inferior to the x distance between the player and the mouse.
		facing = 'E';
	}

	// Create the player's texture and make its name the direction the player is facing.
	std::string texture_name = "Resources/Art/Player/";
	if (blocking) {
		texture_name += "B_";
	}
	texture_name += facing;
	texture_name += ".jpg"; // Temporary art is .jpg, final will probably be .png.

	// Set the player's position.
	sprite.setPosition(sf::Vector2f(position[0], position[1]));

	if (texture_name == current_texture_name) {
		// If the texture and sprite haven't changed since the last frame, only render the player's sprite.
		window.draw(sprite);
	}
	else {
		// Load the new texture onto the player's sprite.
		texture.loadFromFile(texture_name);
		sprite.setTexture(texture);
		sprite.setScale(scale, scale);

		// Render the player's sprite on the window.
		window.draw(sprite);

		// Update the current_texture_name variable.
		current_texture_name = texture_name;
	}
}




// Renders the player's current attack sprite onto the game window.
void Player::render_attack(sf::Clock& global_clock, sf::RenderWindow& window)
{
	// Only render the player's attack if he is attacking.
	if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= A_speed[2] and not blocking)
	{
		// Move the player's attack sprite.
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
		
	
		// Create the player's attack texture and make its name "Resources/Art/Attack/facing_int.jpg", with int a number between 0 and 2 to animate the attack.
		std::string A_texture_name = "Resources/Art/Attack/";
		A_texture_name += facing;

		if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= A_speed[0]) {
			// First frame of the attack animation.
			A_texture_name += "_0";
		}
		else if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= A_speed[1]) {
			// Second frame of the attack animation.
			A_texture_name += "_1";
		}
		else if (global_clock.getElapsedTime().asMilliseconds() - last_A_time <= A_speed[2]) {
			// Last frame of the attack animation.
			A_texture_name += "_2";
		}

		A_texture_name += ".jpg"; // Temporary art is .jpg, final will probably be .png.


		// If the player's attack sprite and texture haven't changed since last frame, only render the attack sprite onto the game window.
		if (A_texture_name == current_A_texture_name) {
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

	// If the player isn't attacking.
	else 
	{
		blocking = false;
	}
}




// Renders the sprite of the player's projectiles onto the game window.
void Player::render_projectiles(sf::Clock& global_clock, sf::RenderWindow& window)
{
	// Render the player's projectiles if they are spawned.
	for (int i = 0; i < 2; i++)
	{
		if (projectile[i].spawned) {
			projectile[i].render(global_clock, window);
		}
	}
}




// Reset the player object.
void Player::reset()
{
	last_dash_time = -1;
	last_A_time = -1;
	last_projectile_time = -1;
	dash_duration = 150;
	dash_cooldown = 700;
	A_cooldown = 500;
	projectile_cooldown = 1000;

	facing = 'S';
	position[0] = 920.0;
	position[1] = 300.0;
	blocking = false;
	scale = 5.0;
	speed = 3.0;
	dash_speed = 3.0;

	hp = 3;

}