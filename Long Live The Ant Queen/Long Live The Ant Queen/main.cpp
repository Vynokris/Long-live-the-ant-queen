/*
Ideas for the game:
- Arcade (meaning it is a minigame that you restart when you loose to get highscores)
- Playing an ant protecting its queen from invader ants
- Topdown
- 1 room only with queen in the center
- Enemies can come from all sides
- Game plays in waves
- Player can purchase upgrades after every wave
*/

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <ctime>

#include <string>
#include <map>


#include "Resources/Classes/classes.h"


// Returns true if the given key is already used for another action.
bool is_key_already_in_use(sf::Keyboard::Key key, sf::Keyboard::Key keybindings[6], int changing_key_index)
{
    for (int i = 0; i < 6; i++) {
        if (key == keybindings[i] and i != changing_key_index) {
            return true;
        }
    }
    return false;
}


// Renders all the entities on the game window in order of ascending y position.
void render_all(sf::RenderWindow& window, Player& player, Queen& queen, Wave& wave)
{
    float y_positions[32] = { player.position[1], queen.position[1] };
    bool rendered[32] = { false, false };
    for (int i = 2; i < 32; i++) {
        y_positions[i] = wave.enemy[i].position[1];
        rendered[i] = false;
    }

    int min = 0;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if (y_positions[j] <= y_positions[min] and not rendered[j]) {
                min = j;
            }
        }

        if (min == 0) {
            player.render(window);
        }
        else if (min == 1) {
            queen.render(window);
        }
        else {
            wave.render_enemy_i(window, min - 2);
        }

        rendered[min] = true;
        min = 0;
    }
}


int main()
{
    // Initialize the random number seed to get different rolls everytime the game is lanched.
    srand(int(time(0)));

    // Initialize the global clock that will mainly be used for cooldowns and animations.
    sf::Clock global_clock;

    // Initialize and open the game window.
	sf::RenderWindow window;
	window.create(sf::VideoMode(1920, 1080), "Long Live The Ant Queen", sf::Style::Close);
    window.setPosition(sf::Vector2i(-8, 0)); // For some reason x = 0 isn't the left part of the screen, so I move the window to x = -8.
    window.setMouseCursorVisible(false); // To hide the mouse pointer.

    // Initialize the keybindings.
    sf::Keyboard::Key keybindings[6] = { sf::Keyboard::Z, sf::Keyboard::S, sf::Keyboard::Q, sf::Keyboard::D, sf::Keyboard::Space, sf::Keyboard::LShift };
    sf::Mouse::Button mousebindings[2] = { sf::Mouse::Left, sf::Mouse::Right };
    int last_pause_time = -100;

    // Set the keybindings to the ones saved in PlayerData. This code is inspired by https://stackoverflow.com/a/6052119/13858872
    std::ifstream in("Resources/PlayerData/keybindings.txt");
    std::string line;
    int counter = 0;
    while (std::getline(in, line)) {
        keybindings[counter] = enum sf::Keyboard::Key(std::stoi(line));
        counter += 1;
    }

    // Initialize the wave object.
    Wave wave;
    wave.start_wave();

    // Initialize the UI object.
    UI ui;

    // Initialize the player object.
    Player player;

    // Initialize the pointer object.
    Pointer pointer;

    // Initialize the queen object.
    Queen queen;

    // Initialize the background sprite.
    sf::Texture background_texture;
    background_texture.loadFromFile("Resources/Art/World/Anthill.png");
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);

    // Initialize the game's inner clock that caps it at 200 fps.
    sf::Clock fps_cap_clock;

    // Initialize a test clock to get the game's fps.
    sf::Clock fps_clock;
    int fps = 0;

	// Start of the game loop.
	while (true)
	{
        // Stop the execution if the window is closed.
        if (not window.isOpen()) {
            // Save the user's keybindings. The following code is inspired by https://stackoverflow.com/a/6052119/13858872
            std::ofstream out("Resources/PlayerData/keybindings.txt");
            for (int i = 0; i < 6; i++) {
                out << keybindings[i] << "\n";
            }
            out.close();

            return 0;
        }

        // Check all the events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            // If the user closed the game window, close the game window.
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                // If the user presses the escape key...
                if (event.key.code == sf::Keyboard::Escape) {
                    // Pause/unpause the game.
                    if (global_clock.getElapsedTime().asMilliseconds() - last_pause_time >= 50) {
                        if (ui.current_screen == 2) {
                            ui.current_screen = 4;
                        }
                        else if (ui.current_screen == 4) {
                            ui.current_screen = 2;
                        }
                        // Quit the options screen.
                        else if (ui.current_screen == 1 and ui.changing_key == -1) {
                            ui.current_screen = ui.last_screen;
                        }
                    }
                }
                // If the user is in the options menu and is changing a key...
                if (ui.current_screen == 1 and ui.changing_key != -1) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        ui.changing_key = -1;
                    }
                    else if (event.key.code <= 25 or event.key.code == 37 or event.key.code == 38 or event.key.code == 57 or event.key.code == 60 or (71 <= event.key.code and event.key.code <= 74)) {
                        if (not is_key_already_in_use(event.key.code, keybindings, ui.changing_key)) {
                            keybindings[ui.changing_key] = event.key.code;
                            ui.changing_key = -1;
                        }
                    }
                }
            }
        }


        if (fps_cap_clock.getElapsedTime().asMilliseconds() >= 5) // This makes the minimal frame duration 5 milliseconds, which means the game runs at 200 fps at max.
        {
            fps_cap_clock.restart();
            fps++;

            // If the user is pressing escape, reset the last pause time.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                last_pause_time = global_clock.getElapsedTime().asMilliseconds();
            }

            // Clear the game window every frame.
            window.clear(sf::Color::Black);


            // If the player is ingame.
            if (ui.current_screen == 4)
            {
                // Process user input to make the player perform actions.
                player.input_logic(global_clock, keybindings, mousebindings, sf::Mouse::getPosition(window));

                // Make the enemies move, apply damage to player, queen and enemies, make the wave end if all the enemies are dead and cause a game over if the queen or player have no more hp.
                wave.wave_logic(global_clock, player, queen, ui);


                // Render the background sprite. The last sprite rendered is over the others.
                window.draw(background_sprite);

                
                // Render the enemies, the queen and the player.
                wave.render_enemies(window);
                queen.render(window);
                player.render(window);

                // Render the attack sprites and projectiles.
                wave.render_enemy_attacks(global_clock, window);
                player.render_attack(global_clock, window);
                player.render_projectiles(global_clock, window);

                /*
                TODO:
                Render the sprites that have the lowest y value first, so that the others are over them.
                This could be done like this:
                - Create a dictionary in this format: {str sprite : int y_pos} with sprite corresponding to the object name (player, queen, enemy_i).
                - Sort the dictionary by ascending y_pos.
                - Loop through the dictionary and render each object in order, based on the sprite value of the dictionary.
                */

                // render_all(window, player, queen, wave);
            }
            else {
                ui.input_logic(global_clock, window, pointer, player, queen, wave);
            }
            

            // Render the UI.
            ui.render(window, pointer, player, queen, wave, keybindings);

            // Render the pointer last for it to be on top of all other sprites.
            pointer.render(window);

            // Update the RenderWindow.
            window.display();
        }

        // Display fps every second.
        if (fps_clock.getElapsedTime().asSeconds() >= 1)
        {
            // std::cout << "Fps: " << fps << "\n";
            fps = 0;
            fps_clock.restart();
        }
	}

	return 0;
}