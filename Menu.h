#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    sf::Font font;
    sf::Text startButton;
    sf::Text instructions;
    bool start;
private:
};
