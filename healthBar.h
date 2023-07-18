#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>


using namespace sf;
using namespace std;
#ifndef HEALTHBAR_H  // If HEALTHBAR_H is not defined yet
#define HEALTHBAR_H


class healthBar{
    private:
        float maxHealth;
        float maxWidth;

    public:
        RectangleShape bar;
        RectangleShape outline;
        healthBar();
        healthBar(float maxHealth, float maxWidth, sf::Vector2f position);
        ~healthBar();
        void update(float currentHealth);
        void draw(RenderWindow *window);
        void move(float xVel, float yVel);
        
};


#endif