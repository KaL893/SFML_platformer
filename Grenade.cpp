#include "Grenade.h"
#include <SFML/Audio.hpp>

// Constructor implementation
#include <iostream>
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "entityStates.h"
using namespace sf;
using namespace std;





// Bullet.cpp
#include "Grenade.h"

// Constructor implementation
Grenade::Grenade(std::string& str, float movementSpeed, Vector2f velocity)
    : Projectile(str, movementSpeed, velocity) {
    this->state = projectileState::Moving;
    this->explosionTexture.loadFromFile("./altSolider/Soldier_1/Explosion.png");
    this->rect = IntRect(384, 0, 100, 85);
    this->animationTimer.restart();
    this->debugClock.restart();
    this->timeSinceThrow.restart();
    this->explosionSound.loadFromFile("grenade.ogg");
    this->currSound.setBuffer(this->explosionSound);
    this->explosionPlayed = false;
    this->currSound.setVolume(100.f);


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


void Grenade::animateExplosion(){
    this->sprite.setTexture(this->explosionTexture);
    if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
        this->rect.left += 128;
        if(this->rect.left >= 1024){
    
            
            this->state = projectileState::Inactive;
        }
        this->animationTimer.restart();
    }
    this->sprite.setTextureRect(this->rect);
}

void Grenade::update(float dt, vector<Sprite*> blocks){

    for(Sprite *g:blocks){
        if(this->sprite.getGlobalBounds().intersects(g->getGlobalBounds())){
           if(this->sprite.getPosition().y <= g->getPosition().y){
                this->state = projectileState::Exploding;
                
                this->sprite.setPosition(this->sprite.getPosition().x, g->getPosition().y-128);
           }
        }
    }

    if(this->state == projectileState::Moving){
        float time = this->timeSinceThrow.getElapsedTime().asSeconds();  // The time elapsed since the grenade was thrown
        float u = this->velocity.y;  // Initial vertical velocity
        float a = 3.2f;  // Acceleration due to gravity, negative because it's acting downward

        float velocityY = u + a * time;  // Vertical velocity
        Vector2f vel(this->velocity.x, velocityY);  // velocity.x is the constant horizontal velocity

        this->sprite.move(vel);  // Move the sprite
    }
    if(this->state == projectileState::Exploding){
        if(!this->explosionPlayed){
            this->currSound.play();
            this->explosionPlayed = true;
        }
        animateExplosion();
    }
}
