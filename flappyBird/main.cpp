#include <iostream>
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "sue");

    sf::CircleShape bird;
    bird.setFillColor(sf::Color::Red);
    bird.setRadius(20);
    bird.setPosition(sf::Vector2f(400, 300));
	
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        window.draw(bird);
        window.display();
    }

	return 0;
}