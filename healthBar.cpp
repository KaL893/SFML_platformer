#include "healthBar.h"

using namespace std;
healthBar::healthBar(float maxHealth, float maxWidth, sf::Vector2f position){
     this->maxHealth = maxHealth;
        this->maxWidth = maxWidth;

        this->outline.setSize(sf::Vector2f(maxWidth, 15)); // 20 is the height, you can adjust this
        this->outline.setFillColor(sf::Color::Transparent);
        this->outline.setOutlineColor(sf::Color::Black);
        this->outline.setOutlineThickness(1);
        this->outline.setPosition(position);
        std::cout << "here" << std::endl;
        this->bar.setSize(sf::Vector2f(maxWidth, 15)); // 20 is the height, you can adjust this
        this->bar.setFillColor(sf::Color::Red);
        this->bar.setPosition(position);
        
}

healthBar::healthBar(){

}

void healthBar::update(float currentHealth)
{
    float percentHealth = currentHealth / maxHealth;
    this->bar.setSize(sf::Vector2f(maxWidth * percentHealth, bar.getSize().y));
}

void healthBar::move(float xVel, float yVel){
    this->bar.move(xVel, yVel);
    this->outline.move(xVel, yVel);
}

void healthBar::draw(sf::RenderWindow *window)
{
    window->draw(this->outline);
    window->draw(this->bar);
}

healthBar::~healthBar(){}