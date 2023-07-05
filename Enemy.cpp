
#include "Enemy.h"


Enemy::Enemy(){
    this->movementTexture.loadFromFile("./altSolider/Soldier_2/walk.png");
    this->idleTexture.loadFromFile("./altSolider/Soldier_1/IdleThree.png");
    this->shootingTexture.loadFromFile("./altSolider/Soldier_1/shooting.png");
    this->rect = IntRect(0, 0, 128, 66);
    this->player.setTexture(this->idleTexture);
    this->player.setTextureRect(this->rect);
    this->gravity = 0.5f;
    this->jumpSpeed = 15.0f;
    this->yVel = 0.0f;
    sf::FloatRect localBounds = player.getLocalBounds();
    this->player.setOrigin(localBounds.left + localBounds.width/2.0f, 
                 localBounds.top  + localBounds.height/2.0f);
    this->player.setPosition(Vector2f(100.0f, 200.0f));
    this->player.setScale(Vector2f(2.0f, 2.0f));
    this->state = movementState::Idle;
    this->lastState = movementState::Idle;
    this->onGround = true;
    this->bulletTimer.restart();
    this->shootingAnimationFinished = true;
    initAnimations();
    this->shootCount = 0;
    this->faceRight = false;
    this->movementRange = movementRange;
    this->movementDirection = 1;
    this->movementSpeed = 2;
}


Enemy::~Enemy(){

}


void Enemy::initAnimations(){
    this->animationTimer.restart();
}
//TODO: MAKE ABSTRACT
void Enemy::updateAnimations(){
    
    
    if(this->state == movementState::Right){
        this->player.setTexture(this->movementTexture);
        
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 896.0f){
                
                this->rect.left = 0.0f;
            }
            this->animationTimer.restart();
        }
        this->player.setTextureRect(this->rect);
        this->player.setScale(Vector2f(2.0f, 2.0f));
    }else if(this->state == movementState::Left){
        this->player.setTexture(this->movementTexture);
        
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 896.0f){
                //std::cout << "Hello, world!" << std::endl;
                this->rect.left = 0.0f;
            }
            this->animationTimer.restart();
        }
        this->player.setTextureRect(this->rect);
        this->player.setScale(Vector2f(-2.f, 2.f));
    }else if(this->state == movementState::Shooting){
        
        this->player.setTexture(this->shootingTexture);
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 384.0f){
                
                //std::cout << "Hello, world!" << std::endl;
                this->rect.left = 0.0f;
                this->state = movementState::Idle;
            }
            this->animationTimer.restart();
        }
        this->player.setTextureRect(this->rect);
        if(this->faceRight){
            this->player.setScale(Vector2f(2.0f, 2.0f));
        }else{
            this->player.setScale(Vector2f(-2.f, 2.f));
        }
        
        
    }
        
    
    
}


//SHOULD BE AN ABSTRACT METHOD

void Enemy::animateIdle() {
    this->player.setTexture(this->idleTexture);
    if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) {
        this->rect.left += 128; // Updated to match sprite width
        
        if (this->rect.left >=  758) { // Updated to match sprite sheet width
            this->rect.left = 0.0f;
        }
        this->animationTimer.restart();
    }
    this->player.setTextureRect(this->rect);
}


void Enemy::update(){
    if(this->player.getPosition().x <= this->movementRange.x){
        this->movementDirection = 1;
        this->state = movementState::Right;
        
    }else if (this->player.getPosition().x >= this->movementRange.y)
    {
        this->movementDirection = -1;
        this->state = movementState::Left;
        
    }

    this->player.move(this->movementDirection * this->movementSpeed, 0);
    updateAnimations();
}
