#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include "logging.hpp"
#include "grid.hpp"
#define DEFAULT_CELL_WIDTH 20
#define DEFAULT_CELL_HEIGHT 20

// TODO: Clean this slop up

int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode(1000, 1000), "Percolation Emergence");

    PercoGrid grid(DEFAULT_CELL_WIDTH, DEFAULT_CELL_HEIGHT, &window);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed){
                switch (event.key.code) {
                    case sf::Keyboard::Escape: {
                        window.close();
                        break;
                    }
                } 
            }
        }

        window.clear(sf::Color::Black);
        grid.draw_grid();
        window.display();

    }

    return 0;
}
