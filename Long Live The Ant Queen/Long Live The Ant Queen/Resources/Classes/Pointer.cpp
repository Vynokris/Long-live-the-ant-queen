#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


#include "classes.h"



// Upon object creation, set its texture and sprite.
Pointer::Pointer()
{
	texture.loadFromFile("Resources/Art/Pointer/Pointer.png");
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
}



// Renders the pointer's sprite at the mouse pointer's position.
void Pointer::render(sf::RenderWindow& window)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	sprite.setPosition(float(mouse_pos.x - sprite.getTextureRect().width * scale / 2), float(mouse_pos.y - sprite.getTextureRect().height * scale / 2));
	window.draw(sprite);
}