
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
    this->shootingFinished = true;
    
}


Enemy::~Enemy(){
    for(bullet *b : this->bullets){
        delete b;
    }
}


void Enemy::initAnimations(){
    this->animationTimer.restart();
    this->shootingAnimationTimer.restart();
}
//TODO: MAKE ABSTRACT
void Enemy::updateAnimations(){
    
    
    if(this->state == movementState::Right){
        this->player.setTexture(this->movementTexture);
        
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.2f){
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
        
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.2f){
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
        if(this->shootingAnimationTimer.getElapsedTime().asSeconds() >= 0.2f){
            this->rect.left += 128.0f;

            if(this->rect.left == 256.0f){
                std::string str = "./Bullet.png";
                Vector2f bulletVelocity;
                if(this->pastState == movementState::Left){
                    bulletVelocity = Vector2f(-1, 0);
                }else{
                    bulletVelocity = Vector2f(1, 0);
                }
                bullet *sb = new bullet(str, 15, bulletVelocity * 15.f);
                if(this->pastState == movementState::Left){
                    sb->sprite.setPosition(this->player.getPosition().x-64,this->player.getPosition().y-40);
                }else{
                    sb->sprite.setPosition(this->player.getPosition().x+64,this->player.getPosition().y-40);
                }
                this->bullets.push_back(sb);
            }
            if(this->rect.left >= 384.0f){
                
                //std::cout << "Hello, world!" << std::endl;
                
                this->rect.left = 0.0f;
               
                this->shootingFinished = true;
                
                this->state = this->pastState;
                
            }
            this->shootingAnimationTimer.restart();
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


void Enemy::render(RenderWindow *target){
    target->draw(this->player);
    for(bullet *b:this->bullets){
        target->draw(b->sprite);
    }
}


void Enemy::update(Sprite *playerSprite){
    if(this->shootingFinished){
        if(this->player.getPosition().x <= this->movementRange.x){
            this->movementDirection = 1;
            this->pastState = this->state;
            this->state = movementState::Right;

        }else if (this->player.getPosition().x >= this->movementRange.y)
        {
            this->movementDirection = -1;
            this->pastState = this->state;
            this->state = movementState::Left;
        }
    }



    if(this->state == movementState::Left){
        if(this->player.getPosition().x -  playerSprite->getPosition().x <= 400){
            if(this->bulletTimer.getElapsedTime().asSeconds() >= 1.5f){
                Vector2f bulletVelocity = Vector2f(-1.f, 0);
                this->bulletTimer.restart();
                this->pastState = this->state;
                this->state = movementState::Shooting;
                this->rect.left = 0;
                this->shootingFinished = false;
            }
        }
    }else if (this->state == movementState::Right)
    {
        if( playerSprite->getPosition().x - this->player.getPosition().x >= 400){
            if(this->bulletTimer.getElapsedTime().asSeconds() >= 1.5f){
                Vector2f bulletVelocity = Vector2f(1, 0);
                std::string str = "./Bullet.png";
                this->bulletTimer.restart();
                this->pastState = this->state;
                this->rect.left = 0;
                this->state = movementState::Shooting;
                this->shootingFinished = false;
            }
        }
    }
    
    for(bullet *b :this->bullets){
        b->update();
    }
    if(this->state != movementState::Shooting){
        this->player.move(this->movementDirection * this->movementSpeed, 0);
    }
    updateAnimations();
}
