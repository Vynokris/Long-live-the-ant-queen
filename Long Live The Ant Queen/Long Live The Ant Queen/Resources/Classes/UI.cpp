#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


#include "classes.h"



// Upon object creation, set the fonts and sprites that the UI will use.
UI::UI()
{
	// Load the fonts that the UI will use.
	font.loadFromFile("Resources/Art/Fonts/dpcomic.ttf");


	// TITLE SCREEN:
	// Give the title text a font.
	t_title.setFont(font);
	t_title.setCharacterSize(120);
	t_title.setFillColor(sf::Color::White);
	t_title.setString("Long live the ant queen!");
	t_title.setPosition(sf::Vector2f(960 - t_title.getLocalBounds().width / 2, 70));

	// Give the play button text a font.
	t_play.setFont(font);
	t_play.setCharacterSize(85);
	t_play.setFillColor(sf::Color::Transparent);
	t_play.setOutlineThickness(1);
	t_play.setOutlineColor(sf::Color::White);
	t_play.setString("Play");
	t_play.setPosition(sf::Vector2f(960 - t_play.getLocalBounds().width / 2, 350));

	// Give the options button text a font.
	t_options.setFont(font);
	t_options.setCharacterSize(85);
	t_options.setFillColor(sf::Color::Transparent);
	t_options.setOutlineThickness(1);
	t_options.setOutlineColor(sf::Color::White);
	t_options.setString("Options");
	t_options.setPosition(sf::Vector2f(960 - t_options.getLocalBounds().width / 2, 600));

	// Give the quit button text a font.
	t_quit.setFont(font);
	t_quit.setCharacterSize(85);
	t_quit.setFillColor(sf::Color::Transparent);
	t_quit.setOutlineThickness(1);
	t_quit.setOutlineColor(sf::Color::White);
	t_quit.setString("Quit");
	t_quit.setPosition(sf::Vector2f(960 - t_quit.getLocalBounds().width / 2, 850));


	// OPTIONS SCREEN:
	// Give the options title text a font.
	o_title.setFont(font);
	o_title.setCharacterSize(150);
	o_title.setFillColor(sf::Color::White);
	o_title.setString("Options");
	o_title.setPosition(sf::Vector2f(960 - o_title.getLocalBounds().width / 2, 70));

	// Initialize all the key textures and sprites.
	for (int i = 0; i < 6; i++) {
		o_key_textures[i].loadFromFile("Resources/Art/Keys/0.png");
		o_key_sprites[i].setTexture(o_key_textures[i]);
		o_key_sprites[i].setScale(sf::Vector2f(5, 5));
	}

	// Give the up key text a font.
	o_up.setFont(font);
	o_up.setCharacterSize(85);
	o_up.setFillColor(sf::Color::Transparent);
	o_up.setOutlineThickness(1);
	o_up.setOutlineColor(sf::Color::White);
	o_up.setString("Move up: ");

	o_up.setPosition(sf::Vector2f(400, 300));
	o_key_sprites[0].setPosition(sf::Vector2f(400 + o_up.getLocalBounds().width, 320));

	// Give the down key text a font.
	o_down.setFont(font);
	o_down.setCharacterSize(85);
	o_down.setFillColor(sf::Color::Transparent);
	o_down.setOutlineThickness(1);
	o_down.setOutlineColor(sf::Color::White);
	o_down.setString("Move down: ");

	o_down.setPosition(sf::Vector2f(400, 400));
	o_key_sprites[1].setPosition(sf::Vector2f(400 + o_down.getLocalBounds().width, 420));

	// Give the left key text a font.
	o_left.setFont(font);
	o_left.setCharacterSize(85);
	o_left.setFillColor(sf::Color::Transparent);
	o_left.setOutlineThickness(1);
	o_left.setOutlineColor(sf::Color::White);
	o_left.setString("Move left: ");

	o_left.setPosition(sf::Vector2f(400, 500));
	o_key_sprites[2].setPosition(sf::Vector2f(400 + o_left.getLocalBounds().width, 520));

	// Give the right key text a font.
	o_right.setFont(font);
	o_right.setCharacterSize(85);
	o_right.setFillColor(sf::Color::Transparent);
	o_right.setOutlineThickness(1);
	o_right.setOutlineColor(sf::Color::White);
	o_right.setString("Move right: ");

	o_right.setPosition(sf::Vector2f(400, 600));
	o_key_sprites[3].setPosition(sf::Vector2f(400 + o_right.getLocalBounds().width, 620));

	// Give the attack key a font.
	o_attack.setFont(font);
	o_attack.setCharacterSize(85);
	o_attack.setFillColor(sf::Color::Transparent);
	o_attack.setOutlineThickness(1);
	o_attack.setOutlineColor(sf::Color::White);
	o_attack.setString("Attack: ");

	o_attack_texture.loadFromFile("Resources/Art/Keys/LeftClick.png");
	o_attack_sprite.setTexture(o_attack_texture);
	o_attack_sprite.setScale(sf::Vector2f(5, 5));

	o_attack.setPosition(sf::Vector2f(1100, 300));
	o_attack_sprite.setPosition(sf::Vector2f(1100 + o_attack.getLocalBounds().width, 320));

	// Give the projectile key a font.
	o_projectile.setFont(font);
	o_projectile.setCharacterSize(85);
	o_projectile.setFillColor(sf::Color::Transparent);
	o_projectile.setOutlineThickness(1);
	o_projectile.setOutlineColor(sf::Color::White);
	o_projectile.setString("Shoot: ");

	o_projectile_texture.loadFromFile("Resources/Art/Keys/RightClick.png");
	o_projectile_sprite.setTexture(o_projectile_texture);
	o_projectile_sprite.setScale(sf::Vector2f(5, 5));

	o_projectile.setPosition(sf::Vector2f(1100, 450));
	o_projectile_sprite.setPosition(sf::Vector2f(1100 + o_projectile.getLocalBounds().width, 470));

	// Give the block key a font.
	o_block.setFont(font);
	o_block.setCharacterSize(85);
	o_block.setFillColor(sf::Color::Transparent);
	o_block.setOutlineThickness(1);
	o_block.setOutlineColor(sf::Color::White);
	o_block.setString("Block: ");

	o_block.setPosition(sf::Vector2f(1100, 600));
	o_key_sprites[5].setPosition(sf::Vector2f(1100 + o_block.getLocalBounds().width, 620));

	// Give the dash key text a font.
	o_dash.setFont(font);
	o_dash.setCharacterSize(85);
	o_dash.setFillColor(sf::Color::Transparent);
	o_dash.setOutlineThickness(1);
	o_dash.setOutlineColor(sf::Color::White);
	o_dash.setString("Dash: ");

	o_dash.setPosition(sf::Vector2f(960 - o_dash.getLocalBounds().width / 2 - o_key_sprites[4].getLocalBounds().width * 2, 720));
	o_key_sprites[4].setPosition(sf::Vector2f(960 + o_dash.getLocalBounds().width / 2 - o_key_sprites[4].getLocalBounds().width * 2, 740));

	// Give the back button text a font.
	o_back.setFont(font);
	o_back.setCharacterSize(85);
	o_back.setFillColor(sf::Color::Transparent);
	o_back.setOutlineThickness(1);
	o_back.setOutlineColor(sf::Color::White);
	o_back.setString("Back");
	o_back.setPosition(sf::Vector2f(960 - o_back.getLocalBounds().width / 2, 950));


	// PAUSE SCREEN:
	// Give the pause title text a font.
	p_title.setFont(font);
	p_title.setCharacterSize(150);
	p_title.setFillColor(sf::Color::White);
	p_title.setString("Paused");
	p_title.setPosition(sf::Vector2f(960 - p_title.getLocalBounds().width / 2, 70));

	// Give the resume button text a font.
	p_resume.setFont(font);
	p_resume.setCharacterSize(85);
	p_resume.setFillColor(sf::Color::Transparent);
	p_resume.setOutlineThickness(1);
	p_resume.setOutlineColor(sf::Color::White);
	p_resume.setString("Resume");
	p_resume.setPosition(sf::Vector2f(960 - p_resume.getLocalBounds().width / 2, 350));

	// Give the options button text a font.
	p_options.setFont(font);
	p_options.setCharacterSize(85);
	p_options.setFillColor(sf::Color::Transparent);
	p_options.setOutlineThickness(1);
	p_options.setOutlineColor(sf::Color::White);
	p_options.setString("Options");
	p_options.setPosition(sf::Vector2f(960 - p_options.getLocalBounds().width / 2, 500));

	// Give the quit to title screen button text a font.
	p_quit_to_title.setFont(font);
	p_quit_to_title.setCharacterSize(85);
	p_quit_to_title.setFillColor(sf::Color::Transparent);
	p_quit_to_title.setOutlineThickness(1);
	p_quit_to_title.setOutlineColor(sf::Color::White);
	p_quit_to_title.setString("Quit to title");
	p_quit_to_title.setPosition(sf::Vector2f(960 - p_quit_to_title.getLocalBounds().width / 2, 650));

	// Give the quit to desktop button text a font.
	p_quit_to_desktop.setFont(font);
	p_quit_to_desktop.setCharacterSize(85);
	p_quit_to_desktop.setFillColor(sf::Color::Transparent);
	p_quit_to_desktop.setOutlineThickness(1);
	p_quit_to_desktop.setOutlineColor(sf::Color::White);
	p_quit_to_desktop.setString("Quit to desktop");
	p_quit_to_desktop.setPosition(sf::Vector2f(960 - p_quit_to_desktop.getLocalBounds().width / 2, 800));


	// UPGRADE SCREEN:
	// Give the wave clear text a font.
	u_wave_clear.setFont(font);
	u_wave_clear.setCharacterSize(85);
	u_wave_clear.setFillColor(sf::Color::White);
	u_wave_clear.setString("Wave clear!");
	u_wave_clear.setPosition(sf::Vector2f(960 - u_wave_clear.getLocalBounds().width / 2, 20));

	// Give the upgrade title a font.
	u_title.setFont(font);
	u_title.setCharacterSize(150);
	u_title.setFillColor(sf::Color::White);
	u_title.setString("Upgrades");
	u_title.setPosition(sf::Vector2f(960 - u_title.getLocalBounds().width / 2, 70));

	// Give the first upgrade a font.
	u_upgrade_0.setFont(font);
	u_upgrade_0.setCharacterSize(85);
	u_upgrade_0.setFillColor(sf::Color::Transparent);
	u_upgrade_0.setOutlineThickness(1);
	u_upgrade_0.setOutlineColor(sf::Color::White);

	// Give the second upgrade a font.
	u_upgrade_1.setFont(font);
	u_upgrade_1.setCharacterSize(85);
	u_upgrade_1.setFillColor(sf::Color::Transparent);
	u_upgrade_1.setOutlineThickness(1);
	u_upgrade_1.setOutlineColor(sf::Color::White);

	// Give the third upgrade a font.
	u_upgrade_2.setFont(font);
	u_upgrade_2.setCharacterSize(85);
	u_upgrade_2.setFillColor(sf::Color::Transparent);
	u_upgrade_2.setOutlineThickness(1);
	u_upgrade_2.setOutlineColor(sf::Color::White);

	// Give the done button a font.
	u_done.setFont(font);
	u_done.setCharacterSize(85);
	u_done.setFillColor(sf::Color::Transparent);
	u_done.setOutlineThickness(1);
	u_done.setOutlineColor(sf::Color::White);
	u_done.setString("Done");
	u_done.setPosition(sf::Vector2f(960 - u_done.getLocalBounds().width / 2, 850));


	// INGAME:
	// Give the hp text a font.
	p_hp.setFont(font);
	p_hp.setCharacterSize(50);
	p_hp.setFillColor(sf::Color::Black);
	p_hp.setPosition(sf::Vector2f(20, 0));

	// Give the hp text a font.
	q_hp.setFont(font);
	q_hp.setCharacterSize(50);
	q_hp.setFillColor(sf::Color::Black);
	q_hp.setPosition(sf::Vector2f(20, 50));

	// Give the wave level text a font.
	wave_lv.setFont(font);
	wave_lv.setCharacterSize(50);
	wave_lv.setFillColor(sf::Color::Black);
	wave_lv.setPosition(sf::Vector2f(1650, 0));


	// GAME OVER SCREEN:
	// Give the title text a font.
	g_title.setFont(font);
	g_title.setCharacterSize(150);
	g_title.setFillColor(sf::Color::Red);
	g_title.setString("Game Over");
	g_title.setPosition(sf::Vector2f(960 - g_title.getLocalBounds().width / 2, 70));

	// Give the kill count text a font.
	g_kill_count.setFont(font);
	g_kill_count.setCharacterSize(85);
	g_kill_count.setFillColor(sf::Color::White);

	// Give the game duration text a font.
	g_game_duration.setFont(font);
	g_game_duration.setCharacterSize(85);
	g_game_duration.setFillColor(sf::Color::White);

	// Give the wave level text a font.
	g_wave_lv.setFont(font);
	g_wave_lv.setCharacterSize(85);
	g_wave_lv.setFillColor(sf::Color::White);

	// Give the score text a font.
	g_score.setFont(font);
	g_score.setCharacterSize(85);
	g_score.setFillColor(sf::Color::White);

	// Give the highscore text a font.
	g_highscore.setFont(font);
	g_highscore.setCharacterSize(75);
	g_highscore.setFillColor(sf::Color::Yellow);
	g_highscore.setPosition(sf::Vector2f(960 - p_resume.getLocalBounds().width / 2, 450));

	// Give the new highscore text a font.
	g_new_highscore.setFont(font);
	g_new_highscore.setCharacterSize(85);
	g_new_highscore.setFillColor(sf::Color::Magenta);
	g_new_highscore.setString("New highscore!");
	g_new_highscore.setRotation(-20);
	g_new_highscore.setPosition(sf::Vector2f(1920 - (g_new_highscore.getLocalBounds().width + 150), 650));

	// Give the back to title button text a font.
	g_back_to_title.setFont(font);
	g_back_to_title.setCharacterSize(85);
	g_back_to_title.setFillColor(sf::Color::Transparent);
	g_back_to_title.setOutlineThickness(1);
	g_back_to_title.setOutlineColor(sf::Color::White);
	g_back_to_title.setString("Back to title");
	g_back_to_title.setPosition(sf::Vector2f(960 - g_back_to_title.getLocalBounds().width / 2, 750));

	// Give the retry button text a font.
	g_retry.setFont(font);
	g_retry.setCharacterSize(85);
	g_retry.setFillColor(sf::Color::Transparent);
	g_retry.setOutlineThickness(1);
	g_retry.setOutlineColor(sf::Color::White);
	g_retry.setString("Retry");
	g_retry.setPosition(sf::Vector2f(960 - g_retry.getLocalBounds().width / 2, 850));
}



// Check collision between the pointer and a text object.
bool UI::text_collision(sf::Text text, Pointer& pointer)
{
	if (text.getGlobalBounds().intersects(pointer.sprite.getGlobalBounds())) {
		return true;
	}
	else {
		return false;
	}
}



// Process user input to click on butons in menus.
void UI::input_logic(sf::Clock& global_clock, sf::RenderWindow& window, Pointer& pointer, Player& player, Queen& queen, Wave& wave)
{
	// Title screen.
	if (current_screen == 0) {
		// If the user clicks on the play button, take him to the ingame screen.
		if (text_collision(t_play, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			current_screen = 4;
			if (wave.wave_lv == 1) {
				wave.game_start_time = int(global_clock.getElapsedTime().asSeconds());
			}
		}
		// If the user clicks on the options button, take him to the options screen.
		else if (text_collision(t_options, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			last_screen = current_screen;
			// o_back.setPosition(sf::Vector2f(960 - o_back.getLocalBounds().width / 2, 950));
			current_screen = 1;
		}
		// If the user clicks on the quit button, quit the game.
		else if (text_collision(t_quit, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			window.close();
		}
	}

	// Options screen.
	else if (current_screen == 1) {
		bool hovering_over_any_key = false;
		for (int i = 0; i < 6; i++) {
			// If the user hovers over a modifiable key, change its sprite.
			if (o_key_sprites[i].getGlobalBounds().intersects(pointer.sprite.getGlobalBounds())) {
				hovering_over_key = i;
				hovering_over_any_key = true;
			}
			// If the user clicks on any of the key sprites, enable him to change it.
			if (o_key_sprites[i].getGlobalBounds().intersects(pointer.sprite.getGlobalBounds()) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				changing_key = i;
			}
		}
		// If the user clicks on the back to title button, take him to the title screen.
		if (text_collision(o_back, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			changing_key = -1;
			current_screen = last_screen;
		}
		// If the player isn't hovering over any key, set the hovering_over_key variable to -1.
		if (not hovering_over_any_key) {
			hovering_over_key = -1;
		}
	}
	

	// Pause screen.
	else if (current_screen == 2) {
		// If the user clicks on the resume button, take him to the ingame screen.
		if (text_collision(p_resume, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			current_screen = 4;
		}
		// If the user clicks on the options button, take him to the options screen.
		else if (text_collision(p_options, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			last_screen = current_screen;
			// o_back.setPosition(sf::Vector2f(960 - o_back.getLocalBounds().width / 2, 850));
			current_screen = 1;
		}
		// If the user clicks on the quit to title button, take him to the title screen.
		else if (text_collision(p_quit_to_title, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			current_screen = 0;
		}
		// If the user clicks on the quit to desktop button, quit the game.
		else if (text_collision(p_quit_to_desktop, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			window.close();
		}
	}

	// Upgrade screen.
	else if (current_screen == 3) {
		// If the user clicks on the first upgrade, select it.
		if (text_collision(u_upgrade_0, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			u_upgrade_chosen = 0;
		}
		// If the user clicks on the second upgrade, select it.
		else if (text_collision(u_upgrade_1, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			u_upgrade_chosen = 1;
		}
		// If the user clicks on the first upgrade, select it.
		else if (text_collision(u_upgrade_2, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			u_upgrade_chosen = 2;
		}
		// If the user clicks on the done button, apply his upgrade, take him to the ingame screen and start a new wave.
		else if (text_collision(u_done, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left) and u_upgrade_chosen != -1) {
			// Apply the chosen upgrade.
			if (upgrades[u_upgrade_chosen] == 0) {
				player.hp += 2;
			}
			else if (upgrades[u_upgrade_chosen] == 1) {
				queen.hp += 2;
			}
			else if (upgrades[u_upgrade_chosen] == 2) {
				player.speed += float(0.2);
			}
			else if (upgrades[u_upgrade_chosen] == 3) {
				player.dash_speed += float(0.2);
			}
			else if (upgrades[u_upgrade_chosen] == 4 and player.A_cooldown >= 250) {
				for (int i = 0; i < 3; i++) {
					player.A_speed[i] -= 25;
					std::cout << player.A_speed[i] << " ";
				}
				player.A_cooldown -= 50;
			}
			else if (upgrades[u_upgrade_chosen] == 5) {
				player.projectile_cooldown -= 75;
			}

			// Reset the chosen upgrade.
			u_upgrade_chosen = -1;

			// Take the player back to the ingame screen.
			current_screen = 4;
		}
	}

	// Game over screen.
	else if (current_screen == 5) {
		// If the user clicks the back to title button, take him to the title screen.
		if (text_collision(g_back_to_title, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			current_screen = 0;
			
			// Reset all the objects.
			global_clock.restart();
			player.reset();
			queen.reset();
			wave.reset();
			wave.start_wave();
		}
		// If the user clicks the retry button, start a new game.
		if (text_collision(g_retry, pointer) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			current_screen = 4;

			// Reset all the objects.
			global_clock.restart();
			player.reset();
			queen.reset();
			wave.reset();
			wave.start_wave();
			wave.game_start_time = int(global_clock.getElapsedTime().asSeconds());
		}
	}
}



// Render all the UI parts onto the game window.
void UI::render(sf::RenderWindow& window, Pointer& pointer, Player& player, Queen& queen, Wave& wave, sf::Keyboard::Key keybindings[5])
{
	// Title screen.
	if (current_screen == 0) 
	{
		// Title text.
		window.draw(t_title);

		// Play button text.
		if (text_collision(t_play, pointer)) {
			t_play.setFillColor(sf::Color::White);
			t_play.setOutlineThickness(0);
		}
		else {
			t_play.setFillColor(sf::Color::Transparent);
			t_play.setOutlineThickness(1);
		}
		window.draw(t_play);

		// Options button text.
		if (text_collision(t_options, pointer)) {
			t_options.setFillColor(sf::Color::White);
			t_options.setOutlineThickness(0);
		}
		else {
			t_options.setFillColor(sf::Color::Transparent);
			t_options.setOutlineThickness(1);
		}
		window.draw(t_options);

		// Quit button text.
		if (text_collision(t_quit, pointer)) {
			t_quit.setFillColor(sf::Color::White);
			t_quit.setOutlineThickness(0);
		}
		else {
			t_quit.setFillColor(sf::Color::Transparent);
			t_quit.setOutlineThickness(1);
		}
		window.draw(t_quit);
	}



	// Options Screen.
	else if (current_screen == 1) 
	{
		// Change the key sprites to the ones set by the player.
		for (int i = 0; i < 6; i++) {
			if (changing_key == i) {
				o_key_textures[i].loadFromFile("Resources/Art/Keys/" + std::to_string(keybindings[i]) + "_press.png");
				o_key_sprites[i].setTexture(o_key_textures[i]);
			}
			else if (hovering_over_key == i) {
				o_key_textures[i].loadFromFile("Resources/Art/Keys/" + std::to_string(keybindings[i]) + "_hover.png");
				o_key_sprites[i].setTexture(o_key_textures[i]);
			}
			else {
				o_key_textures[i].loadFromFile("Resources/Art/Keys/" + std::to_string(keybindings[i]) + ".png");
				o_key_sprites[i].setTexture(o_key_textures[i]);
			}

			if (keybindings[i] == 37) {
				o_key_sprites[i].setTextureRect(sf::IntRect(0, 0, 20, 16));
			}
			else if (keybindings[i] == 38) {
				o_key_sprites[i].setTextureRect(sf::IntRect(0, 0, 24, 16));
			}
			else if (keybindings[i] == 60) {
				o_key_sprites[i].setTextureRect(sf::IntRect(0, 0, 27, 16));
			}
			else if (keybindings[i] == 57) {
				o_key_sprites[i].setTextureRect(sf::IntRect(0, 0, 80, 16));
			}
			else {
				o_key_sprites[i].setTextureRect(sf::IntRect(0, 0, 16, 16));
			}

			// Center the dash key text and sprite.
			if (i == 4) {
				o_dash.setPosition(sf::Vector2f(960 - o_dash.getLocalBounds().width / 2 - o_key_sprites[i].getLocalBounds().width * 2, 720));
				o_key_sprites[i].setPosition(sf::Vector2f(960 + o_dash.getLocalBounds().width / 2 - o_key_sprites[i].getLocalBounds().width * 2, 740));
			}
		}
		
		// Title text.
		window.draw(o_title);
		// Move up key text.
		window.draw(o_up);
		// Move down key text.
		window.draw(o_down);
		// Move left key text.
		window.draw(o_left);
		// Move right key text.
		window.draw(o_right);
		// Attack key text.
		window.draw(o_attack);
		window.draw(o_attack_sprite);
		// Shoot key text and sprite.
		window.draw(o_projectile);
		window.draw(o_projectile_sprite);
		// Block key text and sprite.
		window.draw(o_block);
		// Dash key text.
		window.draw(o_dash);
		// Render the modifiable key sprites.
		for (int i = 0; i < 6; i++) {
			window.draw(o_key_sprites[i]);
		}

		// Back to title button text.
		if (text_collision(o_back, pointer)) {
			o_back.setFillColor(sf::Color::White);
			o_back.setOutlineThickness(0);
		}
		else {
			o_back.setFillColor(sf::Color::Transparent);
			o_back.setOutlineThickness(1);
		}
		window.draw(o_back);
	}



	// Pause screen.
	else if (current_screen == 2) 
	{
		// Title text.
		window.draw(p_title);

		// Resume button text.
		if (text_collision(p_resume, pointer)) {
			p_resume.setFillColor(sf::Color::White);
			p_resume.setOutlineThickness(0);
		}
		else {
			p_resume.setFillColor(sf::Color::Transparent);
			p_resume.setOutlineThickness(1);
		}
		window.draw(p_resume);

		// Options button text.
		if (text_collision(p_options, pointer)) {
			p_options.setFillColor(sf::Color::White);
			p_options.setOutlineThickness(0);
		}
		else {
			p_options.setFillColor(sf::Color::Transparent);
			p_options.setOutlineThickness(1);
		}
		window.draw(p_options);

		// Quit to title button text.
		if (text_collision(p_quit_to_title, pointer)) {
			p_quit_to_title.setFillColor(sf::Color::White);
			p_quit_to_title.setOutlineThickness(0);
		}
		else {
			p_quit_to_title.setFillColor(sf::Color::Transparent);
			p_quit_to_title.setOutlineThickness(1);
		}
		window.draw(p_quit_to_title);

		// Quit to desktop button text.
		if (text_collision(p_quit_to_desktop, pointer)) {
			p_quit_to_desktop.setFillColor(sf::Color::White);
			p_quit_to_desktop.setOutlineThickness(0);
		}
		else {
			p_quit_to_desktop.setFillColor(sf::Color::Transparent);
			p_quit_to_desktop.setOutlineThickness(1);
		}
		window.draw(p_quit_to_desktop);
	}



	// Upgrade screen.
	else if (current_screen == 3) 
	{
		// Wave clear text.
		window.draw(u_wave_clear);
		// Title text.
		window.draw(u_title);
		// First upgrade text.
		if (text_collision(u_upgrade_0, pointer) or u_upgrade_chosen == 0) {
			u_upgrade_0.setFillColor(sf::Color::White);
			u_upgrade_0.setOutlineThickness(0);
		}
		else {
			u_upgrade_0.setFillColor(sf::Color::Transparent);
			u_upgrade_0.setOutlineThickness(1);
		}
		window.draw(u_upgrade_0);
		// Second upgrade text.
		if (text_collision(u_upgrade_1, pointer) or u_upgrade_chosen == 1) {
			u_upgrade_1.setFillColor(sf::Color::White);
			u_upgrade_1.setOutlineThickness(0);
		}
		else {
			u_upgrade_1.setFillColor(sf::Color::Transparent);
			u_upgrade_1.setOutlineThickness(1);
		}
		window.draw(u_upgrade_1);
		// Third upgrade text.
		if (text_collision(u_upgrade_2, pointer) or u_upgrade_chosen == 2) {
			u_upgrade_2.setFillColor(sf::Color::White);
			u_upgrade_2.setOutlineThickness(0);
		}
		else {
			u_upgrade_2.setFillColor(sf::Color::Transparent);
			u_upgrade_2.setOutlineThickness(1);
		}
		window.draw(u_upgrade_2);
		// Done button text.
		if (text_collision(u_done, pointer) and u_upgrade_chosen != -1) {
			u_done.setFillColor(sf::Color::White);
			u_done.setOutlineThickness(0);
		}
		else {
			u_done.setFillColor(sf::Color::Transparent);
			u_done.setOutlineThickness(1);
		}
		window.draw(u_done);
	}



	// Ingame screen.
	else if (current_screen == 4)
	{
		// Set the player hp text to the player's hp.
		p_hp.setString("Player health: " + std::to_string(player.hp));
		window.draw(p_hp);

		// Set the queen hp text to the queen's hp.
		q_hp.setString("Queen health: " + std::to_string(queen.hp));
		window.draw(q_hp);

		// Set the wave level text to the current wave level
		wave_lv.setString("Wave level: " + std::to_string(wave.wave_lv));
		// Move the wave level text to the left if the wave level is too big.
		if (wave.wave_lv > 9 and wave_lv.getPosition().x == 1650) {
			wave_lv.setPosition(sf::Vector2f(1630, 0));
		}
		else if (wave.wave_lv > 99 and wave_lv.getPosition().x == 1630) {
			wave_lv.setPosition(sf::Vector2f(1610, 0));
		}
		// Render the wave level.
		window.draw(wave_lv);
	}



	// Game over screen.
	else
	{
		// Title text.
		window.draw(g_title);

		// Kill count text.
		window.draw(g_kill_count);

		// Game duration text.
		window.draw(g_game_duration);

		// Wave level text.
		window.draw(g_wave_lv);

		// Score texte.
		window.draw(g_score);

		// Highscore text.
		window.draw(g_highscore);

		// New highscore text.
		window.draw(g_new_highscore);

		// Back to title screen button text.
		if (text_collision(g_back_to_title, pointer)) {
			g_back_to_title.setFillColor(sf::Color::White);
			g_back_to_title.setOutlineThickness(0);
		}
		else {
			g_back_to_title.setFillColor(sf::Color::Transparent);
			g_back_to_title.setOutlineThickness(1);
		}
		window.draw(g_back_to_title);
		
		// Retry button text.
		if (text_collision(g_retry, pointer)) {
			g_retry.setFillColor(sf::Color::White);
			g_retry.setOutlineThickness(0);
		}
		else {
			g_retry.setFillColor(sf::Color::Transparent);
			g_retry.setOutlineThickness(1);
		}
		window.draw(g_retry);
	}
}