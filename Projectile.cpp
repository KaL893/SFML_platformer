
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "math.h"
Projectile::Projectile(std::string& str, float movementSpeed, Vector2f velocity){
    this->texture.loadFromFile(str);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(Vector2f(1.5f, 1.5f));
    this->movementSpeed = movementSpeed;
    this->active = true;
    this->velocity = velocity;

}


Projectile::~Projectile(){
    
}

void Projectile::update(View currentView)
{

    float viewLeft = currentView.getCenter().x - currentView.getSize().x / 2;
    float viewRight = currentView.getCenter().x + currentView.getSize().x / 2;
    float viewTop = currentView.getCenter().y - currentView.getSize().y / 2;
    float viewBottom = currentView.getCenter().y + currentView.getSize().y / 2;
    sf::FloatRect viewBounds(viewLeft, viewTop, viewRight - viewLeft, viewBottom - viewTop);

    if (!(viewBounds.intersects(this->sprite.getGlobalBounds()))) {
      this->active = false;  
    } 

    if(this->active){
        this->sprite.move(this->velocity);
    }
}
