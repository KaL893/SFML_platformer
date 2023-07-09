#include "Grenade.h"


// Constructor implementation
#include <iostream>
#include <SFML/Graphics.hpp>
#include "bullet.h"
using namespace sf;





// Bullet.cpp
#include "Grenade.h"

// Constructor implementation
Grenade::Grenade(std::string& str, float movementSpeed, Vector2f velocity)
    : Projectile(str, movementSpeed, velocity) {
    // Additional initialization here.
}

// Destructor implementation
Grenade::~Grenade() {
    // Additional cleanup here.
}


void Grenade::setGravity(float gravity){
    this->gravity = gravity;

}

void Grenade::setInitPos(Vector2f initPos, Vector2f direction){
    this->initialPos = initPos;
    this->sprite.setPosition(initPos);
    this->direction = direction;

}

void Grenade::update(float dt){
    if(this->active){
        Vector2f currPos = this->sprite.getPosition();
        float horizDisplacement = currPos.x - initialPos.x;
        float velocityY;
        if(this->direction.x > 0){
             velocityY = ((-4*this->direction.y)/(this->direction.x*this->direction.x))*(2*horizDisplacement - this->direction.x) ; 
        }else{
             velocityY = ((-4*this->direction.y)/(-this->direction.x*this->direction.x))*(2*horizDisplacement + this->direction.x) ;
        }
        
        Vector2f vel(this->velocity.x, velocityY); // velocity.x is the constant horizontal velocity

        this->sprite.move(vel * this->movementSpeed);

    }
}
