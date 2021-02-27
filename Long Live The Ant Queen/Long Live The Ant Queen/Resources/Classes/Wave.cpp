#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>


#include "classes.h"



// Start a new wave.
void Wave::start_wave()
{
	// Update the wave level.
	wave_lv += 1;
	
	// Choose the number of enemies.
	if (wave_lv <= 5) {
		num_of_enemies = wave_lv;
	}
	else if (wave_lv < 30) {
		num_of_enemies = rand() % 5 + wave_lv - 5;
	}
	else {
		num_of_enemies = rand() % 10 + 20;
	}

	std::cout << "\nNew wave! Wave level: " << wave_lv << "\nNumber of enemies in this wave: " << num_of_enemies << "\n";

	// Spawn the enemies in random positions.
	for (int i = 0; i < num_of_enemies; i++) {
		int rand_pos = rand() % 4;

		if (rand_pos == 0) {
			enemy[i].spawn(wave_lv, float(rand() % 1920), 0);
		}
		else if (rand_pos == 1) {
			enemy[i].spawn(wave_lv, float(rand() % 1920), 1080);
		}
		else if (rand_pos == 2) {
			enemy[i].spawn(wave_lv, 0, float(rand() % 1080));
		}
		else {
			enemy[i].spawn(wave_lv, 1920, float(rand() % 1080));
		}
	}
}



// End the current wave.
void Wave::end_wave(UI& ui, Player& player)
{
	// Add (wave_lv*player.kills_in_current_wave) to the player's score.
	player.score += wave_lv * player.kills_in_current_wave;

	// Start a new wave.
	start_wave();

	// Reset the number of kills of the player in the current wave.
	player.kills_in_current_wave = 0;

	// Change the current screen to the upgrade screen.
	ui.current_screen = 3;

	// Chose random upgrades.
	int upgrade_0 = rand() % 6;
	int upgrade_1 = rand() % 6;
	while (upgrade_0 == upgrade_1) {
		upgrade_1 = rand() % 6;
	}
	int upgrade_2 = rand() % 6;
	while (upgrade_0 == upgrade_2 or upgrade_1 == upgrade_2) {
		upgrade_2 = rand() % 6;
	}
	ui.upgrades[0] = upgrade_0;
	ui.upgrades[1] = upgrade_1;
	ui.upgrades[2] = upgrade_2;

	// Set the first upgrade text.
	if (upgrade_0 == 0) {
		ui.u_upgrade_0.setString("Player HP up");
	}
	else if (upgrade_0 == 1) {
		ui.u_upgrade_0.setString("Queen HP up");
	}
	else if (upgrade_0 == 2) {
		ui.u_upgrade_0.setString("Move speed up");
	}
	else if (upgrade_0 == 3) {
		ui.u_upgrade_0.setString("Dash speed up");
	}
	else if (upgrade_0 == 4) {
		ui.u_upgrade_0.setString("Attack speed up");
	}
	else if (upgrade_0 == 5) {
		ui.u_upgrade_0.setString("Shooting speed up");
	}
	ui.u_upgrade_0.setPosition(sf::Vector2f(960 - ui.u_upgrade_0.getLocalBounds().width / 2, 350));

	// Set the second upgrade text.
	if (upgrade_1 == 0) {
		ui.u_upgrade_1.setString("Player HP up");
	}
	else if (upgrade_1 == 1) {
		ui.u_upgrade_1.setString("Queen HP up");
	}
	else if (upgrade_1 == 2) {
		ui.u_upgrade_1.setString("Move speed up");
	}
	else if (upgrade_1 == 3) {
		ui.u_upgrade_1.setString("Dash speed up");
	}
	else if (upgrade_1 == 4) {
		ui.u_upgrade_1.setString("Attack speed up");
	}
	else if (upgrade_1 == 5) {
		ui.u_upgrade_1.setString("Shooting speed up");
	}
	ui.u_upgrade_1.setPosition(sf::Vector2f(960 - ui.u_upgrade_1.getLocalBounds().width / 2, 500));

	// Set the third upgrade text.
	if (upgrade_2 == 0) {
		ui.u_upgrade_2.setString("Player HP up");
	}
	else if (upgrade_2 == 1) {
		ui.u_upgrade_2.setString("Queen HP up");
	}
	else if (upgrade_2 == 2) {
		ui.u_upgrade_2.setString("Move speed up");
	}
	else if (upgrade_2 == 3) {
		ui.u_upgrade_2.setString("Dash speed up");
	}
	else if (upgrade_2 == 4) {
		ui.u_upgrade_2.setString("Attack speed up");
	}
	else if (upgrade_2 == 5) {
		ui.u_upgrade_2.setString("Shooting speed up");
	}
	ui.u_upgrade_2.setPosition(sf::Vector2f(960 - ui.u_upgrade_2.getLocalBounds().width / 2, 650));
}



// Make the enemies move, apply damage to player, queen and enemies, make the wave end if all the enemies are dead and cause a game over if the queen or player have no more hp.
void Wave::wave_logic(sf::Clock& global_clock, Player& player, Queen& queen, UI& ui)
{
	// Loop through all the enemies.
	for (int i = 0; i < num_of_enemies; i++) {
		// Move the enemy towards its focus.
		if (enemy[i].player_focus) {
			float player_pos[2] = { player.position[0] + 8 * 5, player.position[1] + 8 * 5 }; // I need to create this temp variable to send the coordinates of the center of the player.
			enemy[i].move_logic(global_clock, player_pos);
		}
		else {
			enemy[i].move_logic(global_clock, queen.position);
		}

		// Check for damage on player, queen and enemy.
		player.damage_logic(global_clock, enemy[i]);
		queen.damage_logic(global_clock, enemy[i]);
		enemy[i].damage_logic(global_clock, player);
	}

	// Check if there are still enemies alive.
	bool all_enemies_killed = true;
	for (int i = 0; i < num_of_enemies; i++) {
		if (enemy[i].hp > 0) {
			all_enemies_killed = false;
			i = num_of_enemies; // End the loop.
		}
	}

	// If all the wave's enemies have been killed, end the current wave.
	if (all_enemies_killed) {
		end_wave(ui, player);
	}
	
	// If the player or the queen's hp are under 0, it is GAME OVER.
	if (player.hp <= 0 or queen.hp <= 0) {
		// Set the game's end time.
		game_end_time = int(global_clock.getElapsedTime().asSeconds());

		// Calculate the game duration.
		int game_duration = game_end_time - game_start_time;

		// Calculate the player's score.
		player.score *= game_duration;

		// Generate the kill count text.
		ui.g_kill_count.setString("Kill count: " + std::to_string(player.kills));
		ui.g_kill_count.setPosition(sf::Vector2f(960 - ui.g_kill_count.getLocalBounds().width / 2, 300));

		// Generate the game duration text.
		ui.g_game_duration.setString("Game duration: " + std::to_string(game_duration) + " seconds.");
		ui.g_game_duration.setPosition(sf::Vector2f(960 - ui.g_game_duration.getLocalBounds().width / 2, 400));

		// Generate the wave level text.
		ui.g_wave_lv.setString("Wave level: " + std::to_string(wave_lv));
		ui.g_wave_lv.setPosition(sf::Vector2f(960 - ui.g_wave_lv.getLocalBounds().width / 2, 500));

		// Generate the score text.
		ui.g_score.setString("Score: " + std::to_string(player.score));
		ui.g_score.setPosition(sf::Vector2f(960 - ui.g_score.getLocalBounds().width / 2, 600));



		// Check the player's highscore and modify it if the game duration is higher. The following code is inspired by https://stackoverflow.com/a/6052119/13858872
		std::ifstream in("Resources/PlayerData/highscore.txt");
		int highscore = 0;
		in >> highscore;
		in.close();

		if (highscore < player.score) {
			std::ofstream out("Resources/PlayerData/highscore.txt");
			out << player.score;
			out.close();
		}

		// Set the highscore text and its position.
		ui.g_highscore.setString("Highscore: " + std::to_string(highscore));
		// ui.g_highscore.setPosition(sf::Vector2f(960 - ui.g_highscore.getLocalBounds().width / 2, 600));
		ui.g_highscore.setPosition(sf::Vector2f(250, 500));
		ui.g_highscore.setRotation(20);

		// Set the new highscore text if the player has a new highscore.
		if (highscore < game_duration) {
			ui.g_new_highscore.setString("New highscore!");
		}
		else {
			ui.g_new_highscore.setString("");
		}

		// Go to the game over screen.
		ui.current_screen = 5;
	}
}



// Render the enemies' sprites onto the game window.
void Wave::render_enemies(sf::RenderWindow& window)
{
	for (int i = 0; i < num_of_enemies; i++) {
		enemy[i].render(window);
	}
}



// Only render the enemy of index i
void Wave::render_enemy_i(sf::RenderWindow& window, int i)
{
	enemy[i].render(window);
}



// Render the sprite of the attacks and projectiles of the enemies onto the game window.
void Wave::render_enemy_attacks(sf::Clock& global_clock, sf::RenderWindow& window)
{
	for (int i = 0; i < num_of_enemies; i++) {
		enemy[i].render_attack(global_clock, window);
		enemy[i].render_projectiles(global_clock, window);
	}
}



// Reset the wave object.
void Wave::reset()
{
	wave_lv = 0;
	num_of_enemies = 0;
	game_start_time = -1;
	game_end_time = -1;
	for (int i = 0; i < total_num_of_enemies; i++) {
		enemy[i].reset();
		if (enemy[i].weapon == 1) {
			enemy[i].projectile.despawn();
		}
	}
}