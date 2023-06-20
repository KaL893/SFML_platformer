#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
using namespace sf;

// struct Frame{

// }


Player::Player(){
    curTexture.loadFromFile("./altSolider/Soldier_1/Walk.png");
    idleTexture.loadFromFile("./altSolider/Soldier_1/Idle.png");
    this->rect = IntRect(0, 0, 128, 128);
    player.setTexture(idleTexture);
    player.setTextureRect(this->rect);
    player.setPosition(Vector2f(100.0f, 200.0f));
    player.setScale(Vector2f(2.0f, 2.0f));
    

    initAnimations();
    

};

Player::~Player(){
    
}


void Player::initAnimations(){
    this->animationTimer.restart();
}

void Player::updateAnimations(){
    
    if(this->moving){
        player.setTexture(curTexture);
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 512.0f){
                std::cout << "Hello, world!" << std::endl;
                this->rect.left = 256.0f;
            }
            this->animationTimer.restart();
        }
        player.setTextureRect(this->rect);
        
    }else{
    }
}
void Player::animateIdle() {
    player.setTexture(idleTexture);
    if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
        std::cout << "rect.left: " << this->rect.left << std::endl;
        this->rect.left += 128; // Updated to match sprite width
        
        if (this->rect.left >=  758) { // Updated to match sprite sheet width
            this->rect.left = 0.0f;
        }
        this->animationTimer.restart();
    }
    player.setTextureRect(this->rect);
}


