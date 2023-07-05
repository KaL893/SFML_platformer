
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

void Projectile::update(){
    if(this->active){
        this->sprite.move(this->velocity);
    }
}
