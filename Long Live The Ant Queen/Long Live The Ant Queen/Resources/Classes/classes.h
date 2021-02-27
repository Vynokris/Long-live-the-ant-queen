#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <map>




// Forward declarations of all the classes so that I can use them inside functions without problems (like if I call a class before it is created).
class Pointer;
class Projectile;
class Player;
class Enemy;
class Queen;
class UI;
class Wave;



class Pointer
{
public:
	sf::Texture texture;						// Pointer's texture.
	sf::Sprite sprite;							// Pointer's sprite.

	float scale = 3.0;							// Multiplyer for the pointer's base sprite size (16x16).


	// Upon object creation, set its texture and sprite.
	Pointer();

	// Renders the pointer's sprite at the mouse pointer's position.
	void render(sf::RenderWindow& window);
};




class Projectile
{
public:
	sf::Texture texture;						// Projectile's texture.
	sf::Sprite sprite;							// Projectile sprite.
	
	bool spawned = false;						// This boolean is true if the projectile has been spawned and not yet despawned. It means the projectile should move and be rendered on the game window.
	int spawn_time = -1;						// This variable stores the moment (in ms) when the projectile was spawned. Set to -1 if the projectile has not been spawned.
	float direction[2] = { 0.0, 0.0 };			// Projectile's direction.
	float scale = 5.0;							// Multiplyer for the projectile's base sprite size (16x16).
	int speed = 5;								// Multiplyer for the projectile's base movement speed (which is based on its direction).
	int max_lifetime = 1000;					// This is the maximum lifetime of the projectile (in milliseconds). When the projectile's lifetime exceeds this value, it despawns.


	// Upon object creation, set its texture and sprite.
	Projectile();

	// Spawn the projectile at the player's position and with the right direction.
	void spawn(sf::Clock& global_clock, float player_position[2], float projectile_direction[2]);

	// Despawn the projectile.
	void despawn();

	// If the projectile hasn't exceeded its max_lifetime, make it move in function of its direction, then render it onto the game window.
	void render(sf::Clock& global_clock, sf::RenderWindow& window);
};




class Player
{
public:
	sf::Texture texture;						// Player's texture.
	std::string current_texture_name = "";		// Player's current texture name.
	sf::Sprite sprite;							// Player's sprite.
	sf::Texture A_texture;						// Texture of the player's attack.
	std::string current_A_texture_name = "";	// Player's current attack texture name.
	sf::Sprite A_sprite;						// Sprite of the player's attack.

	int last_dash_time = -1;					// This variable is set to the global_clock time every time the player dashes. It enables the dash cooldown. Set to -1 if the player never attacked.
	int last_A_time = -1;						// This variable is set to the global_clock time every time the player does a close range attack. It enables the attack animation and the attack cooldown. Set to -1 if the player never attacked.
	int last_projectile_time = -1;				// This variable is set to the global_clock time every time the player does a long range attack. It enables a cooldown on this type of attack. Set to -1 if the player never attacked.
	int dash_duration = 150;					// Duration of the player's dash (in milliseconds).
	int dash_cooldown = 700;					// Cooldown for the player's dash (in milliseconds).
	int A_speed[3] = { 100, 200, 300 };			// Speed of the animation (the first value is the time when the first frame ends, the second when the second frame ends and the last when the third frame ends).
	int A_cooldown = 500;						// Cooldown for the player's close range attack (in milliseconds).
	int projectile_cooldown = 1000;				// Cooldown for the player's long range attack (in milliseconds).

	char facing = 'S';							// Player's current direction. N for North, S for South, W for West, E for East.
	float position[2] = { 920.0, 300.0 };		// Player's x and y position on the game window.
	bool blocking = false;						// true if the player is blocking, false if not.
	float scale = 5.0;							// Multiplyer for the player's base sprite size (16x16).
	float speed = 3.0;							// Multiplyer for the player's base movement speed (1px per frame).
	float dash_speed = 3.0;						// Multiplyer that stacks on the speed multiplyer during the duration of a dash.

	int hp = 3;									// Player's hp.
	int kills = 0;								// Number of enemies the player has killed.
	int kills_in_current_wave = 0;				// Number of enemies the player has killed in the current wave. Reset at the start of every wave.
	int score = 0;								// The player's score. At the end of each wave, (wave_lv*player_kills_in_current_wave) is added to it. Upon game over, it is multiplied by the game duration.
	Projectile projectile[2];					// Player's projectiles. They will be spawned if the player performs a long range attack.


	// Upon object creation, do nothing.
	Player();

	// Returns a string of len 4. 
	// The 1st char is 't' if the player is colliding with the top border of the window, 'f' if not. 
	// The 2nd is for the bottom.
	// The 3rd for the left.
	// The 4th for the right.
	std::string colliding_with_border();

	// Processes user input and calls the adequate functions (walk, dash, attack, block, pause).
	void input_logic(sf::Clock& global_clock, sf::Keyboard::Key keybindings[6], sf::Mouse::Button mousebindings[2], sf::Vector2i mouse_pos);

	// Moves the player's sprite in the direction given by x and y. x and y must be either 1, 0 or -1.
	void move(sf::Clock& global_clock, float x, float y);

	// Makes the player dash by updating the last dash time if the cooldown is finished.
	void dash(sf::Clock& global_clock);

	// Makes the player attack (type argument: 0=close attack, 1=ranged attack, 2=block).
	void attack(sf::Clock& global_clock, int type, sf::Vector2i mouse_pos);

	// Enables the player to take damage from the enemies.
	void damage_logic(sf::Clock& global_clock, Enemy& enemy);

	// Renders the player's current sprite onto the game window.
	void render(sf::RenderWindow& window);

	// Renders the player's current attack sprite onto the game window.
	void render_attack(sf::Clock& global_clock, sf::RenderWindow& window);

	// Renders the sprite of the player's projectiles onto the game window.
	void render_projectiles(sf::Clock& global_clock, sf::RenderWindow& window);

	// Resets the player object.
	void reset();
};




class Enemy
{
public:
	sf::Texture texture;						// Enemy's texture.
	std::string current_texture_name = "";		// Enemy's current texture name.
	sf::Sprite sprite;							// Enemy's sprite.
	sf::Texture A_texture;						// Texture of the enemy's attack.
	std::string current_A_texture_name = "";	// Enemy's current attack texture name.
	sf::Sprite A_sprite;						// Sprite of the enemy's attack.
	int last_A_time = -1;						// This value is set to the global_clock value every time the enemy attack. It enables the attack animation and the attack cooldown. Set to -1 if the enemy hasn't attacked yet.

	char facing = 'S';							// Enemy's current direction. N for North, S for South, W for West, E for East.
	float position[2] = { 0.0, 0.0 };			// Enemy's x and y coordinates on the game window.
	float scale = 5.0;							// Multiplyer for the enemy's base sprite size (16x16).
	float speed = 0.5;							// Multiplyer for the player's base movement speed (1px per frame).

	int hp = 0;									// Enemy's hp. Set to 0 before being spawned.
	bool weapon = 0;							// 0 = close range attacks, 1 = long range attacks.
	Projectile projectile;						// Enemy's projectile.
	bool player_focus = false;					// 0 = focus on the queen, 1 = focus on the player.
	bool taken_damage = false;					// This variable is set to true if the enemy has taken damage from a player close range attack. It is set back to false at the end of the attack.
												//		This makes it so that the enemy can only be damaged once per attack.
	bool damaged_queen = false;					// This variable is set to true if the enemy has damaged the queen with a close range attack. It is set back to false at the end of the attack.
												//		This makes it so that the enemy can only damage the queen once per attack.
	bool damaged_player = false;				// This variable is set to true if the enemy has damaged the queen with a close range attack. It is set back to false at the end of the attack.
												//		This makes it so that the enemy can only damage the queen once per attack.


	// Upon object creation, do nothing.
	Enemy();

	// Set the enemy's hp and weapon based on the level argument.
	void spawn(int lv, float x, float y);

	// Makes the enemy move towards its focus until close enough to attack.
	void move_logic(sf::Clock& global_clock, float focus_pos[2]);

	// Makes the enemy attack in function of the distance to its focus and according to a cooldown.
	void attack_logic(sf::Clock& global_clock, float focus_pos[2]);

	// Enables the enemy to take damage from the player.
	void damage_logic(sf::Clock& global_clock, Player& player);

	// Makes the enemy disappear and potentially drop something if its hp is at 0.
	void kill();

	// Renders the enemy's current sprite onto the game window.
	void render(sf::RenderWindow& window);

	// Renders the enemy's current attack sprite onto the game window.
	void render_attack(sf::Clock& global_clock, sf::RenderWindow& window);

	// Renders the sprite of the enemy's projectiles onto the game window.
	void render_projectiles(sf::Clock& global_clock, sf::RenderWindow& window);

	// Reset the enemy object.
	void reset();
};




class Queen
{
public:
	sf::Texture texture;						// Queen's texture.
	sf::Sprite sprite;							// Queen's sprite.

	float position[2] = { 960.0, 500.0 };		// Queen's x and y coordinates on the game window.
	float scale = 5.0;							// Multiplyer for the queen's base sprite size (16x16).

	int hp = 5;									// Queen's hp.
	bool taken_damage = false;					// This variable is set to true if the queen has taken damage from an enemy's close range attack. It is set back to false at the end of the attack.
												//		This makes it so that the queen can only be damaged once per attack.


	// Upon object creation, set its texture and sprite.
	Queen();

	// Enables the queen to take damage from the enemies.
	void damage_logic(sf::Clock& global_clock, Enemy& enemy);

	// Renders the queen's sprite onto the game window.
	void render(sf::RenderWindow& window);

	// Reset the queen object.
	void reset();
};




class UI
{
public:
	int current_screen = 0;						// 0 = title screen, 1 = options screen, 2 = pause screen, 3 = upgrade screen, 4 = ingame, 5 = game over.

	sf::Font font;								// Font used for the text of the UI.

	// Title screen:
	sf::Text t_title;							// Text that reads: "Long live the ant queen".
	sf::Text t_play;							// Text that starts a new game when clicked.
	sf::Text t_options;							// Text that takes the user to the options screen when clicked.
	sf::Text t_quit;							// Text that closes the game when clicked.

	// Options screen:
	int last_screen = -1;						// This variable stores the screen that was before the options screen to take back the user to it when he presses "Back".
	int changing_key = -1;						// This variable changes when the user is modifying a keybindings. It is set to the key he is changing. Set back to -1 when done.
	int hovering_over_key = -1;					// This variable changes to the key that the player is hovering over. Set to -1 when no key is hovered over.

	sf::Text o_title;							// Text that reads: "Options".

	sf::Text o_up;								// Text that reads: "Move up:".
	sf::Text o_down;							// Text that reads: "Move down:".
	sf::Text o_left;							// Text that reads: "Move left:".
	sf::Text o_right;							// Text that reads: "Move right:".
	sf::Text o_block;							// Text that reads: "Block:".
	sf::Text o_dash;							// Text that reads: "Dash:".

	sf::Texture o_key_textures[6];				// Array for all of the textures of the modifiable keys.
	sf::Sprite o_key_sprites[6];				// Array for all of the sprites of the modifiable keys.

	sf::Text o_attack;							// Text that reads: "Attack:".
	sf::Texture o_attack_texture;				// Texture that gets loaded on the o_attack_sprite.
	sf::Sprite o_attack_sprite;					// Sprite that shows the key used to attack. If clicked, the user is able to change this key.

	sf::Text o_projectile;						// Text that reads: "Shoot:".
	sf::Texture o_projectile_texture;			// Texture that gets loaded on the o_projectile_sprite.
	sf::Sprite o_projectile_sprite;				// Sprite that shows the key used to shoot a projectile. If clicked, the user is able to change this key.

	sf::Text o_back;							// Text that takes the user back to the last screen he was on when clicked.

	// Pause menu:
	sf::Text p_title;							// Text that reads: "Paused".
	sf::Text p_resume;							// Text that resumes the game when clicked.
	sf::Text p_options;							// Text that takes the user to the options screen when clicked.
	sf::Text p_quit_to_title;					// Text that takes the user to the title screen when clicked.
	sf::Text p_quit_to_desktop;					// Text that closes the game when clicked.

	// Upgrade screen:
	int upgrades[3] = { -1, -1, -1 };			// Upgrades the user can choose from. 0 = player hp up, 1 = queen hp up, 2 = move speed up, 3 = dash speed up, 4 = close attack speed up, 5 = projectile shoot speed up.
	int u_upgrade_chosen = -1;					// Takes the value of the chosen upgrade.

	sf::Text u_wave_clear;						// Text that reads "Wave clear!".
	sf::Text u_title;							// Text that reads "Upgrade".
	sf::Text u_upgrade_0;						// Text that shows the first upgrade.
	sf::Text u_upgrade_1;						// Text that shows the second upgrade.
	sf::Text u_upgrade_2;						// Text that shows the third upgrade.
	sf::Text u_done;							// Text that reads "Done". When the player clicks it, he gets the upgrade he chose and move on to the next wave.

	// Ingame:
	sf::Text p_hp;								// Text that shows the hp of the player.
	sf::Text q_hp;								// text that shows the hp of the queen.
	sf::Text wave_lv;							// Text that shows the current wave level.

	// Game Over screen:
	sf::Text g_title;							// Text that reads "Game Over".
	sf::Text g_kill_count;						// Text that shows the player's kill count.
	sf::Text g_game_duration;					// Text that shows the game's duration.
	sf::Text g_wave_lv;							// Text that shows the final wave level of the game.
	sf::Text g_score;							// Text that shows the player's score.
	sf::Text g_highscore;						// Text that shows the player's best time.
	sf::Text g_new_highscore;					// Text that reads "New Highscore!" if the player has a new best time.
	sf::Text g_back_to_title;					// Text that reads "Back to title". When the user clicks it, he goes back to the title screen.
	sf::Text g_retry;							// Text that reads "Retry". When the user clicks it, a new game starts.


	// Upon object creation, set the fonts and sprites that the UI will use.
	UI();

	// Check collision between the pointer and a text object.
	bool text_collision(sf::Text text, Pointer& pointer);

	// Process user input to click on butons in menus.
	void input_logic(sf::Clock& global_clock, sf::RenderWindow& window, Pointer& pointer, Player& player, Queen& queen, Wave& wave);

	// Render all the UI objects onto the game window.
	void render(sf::RenderWindow& window, Pointer& pointer, Player& player, Queen& queen, Wave& wave, sf::Keyboard::Key keybindings[6]);
};




class Wave
{
public:
	int wave_lv = 0;							// Wave level. Goes up by 1 every time a new wave starts.

	int total_num_of_enemies = 30;				// The total number of enemies.
	Enemy enemy[30];							// A number of these enemies will be spawned every wave.

	int num_of_enemies = 0;						// Stores the number of enemies at the start of each wave.

	int game_start_time = -1;					// Stores the time at which the player started his game.
	int game_end_time = -1;						// Stores the time at which the player had a game over.


	// Start a new wave.
	void start_wave();

	// End a wave.
	void end_wave(UI& ui, Player& player);

	// Make the enemies move, apply damage to player, queen and enemies, make the wave end if all the enemies are dead and cause a game over if the queen or player have no more hp.
	void wave_logic(sf::Clock& global_clock, Player& player, Queen& queen, UI& ui);

	// Render the enemies that are alive in this wave onto the game window.
	void render_enemies(sf::RenderWindow& window);

	// Render only the enemy of index i.
	void render_enemy_i(sf::RenderWindow& window, int i);

	// Render the sprite of the attacks and projectile of the enemies onto the game window.
	void render_enemy_attacks(sf::Clock& global_clock, sf::RenderWindow& window);

	// Reset the wave object.
	void reset();
};