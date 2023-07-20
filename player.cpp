#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Animation.h"
#include "math.h"
#include <SFML/Audio.hpp>
#include <vector>

using namespace sf;
using namespace std;



Player::Player() {
    this->movementTexture.loadFromFile("./altSolider/Soldier_1/runTwo.png");
    this->idleTexture.loadFromFile("./altSolider/Soldier_1/IdleThree.png");
    this->shootingTexture.loadFromFile("./altSolider/Soldier_1/shooting.png");
    this->hurtTexture.loadFromFile("./altSolider/Soldier_1/hurtEdited.png");
    this->throwingTexture.loadFromFile("./altSolider/Soldier_1/Grenade.png");
    this->rect = IntRect(0, 0, 128, 66);
    this->player.setTexture(this->idleTexture);
    this->player.setTextureRect(this->rect);
    this->gravity = 0.5f;
    this->jumpSpeed = 15.0f;
    this->yVel = 0.0f;

    sf::FloatRect localBounds = player.getLocalBounds();
    sf::IntRect rect = player.getTextureRect();
    
    
    
    
// Set the origin of your sprite to its center
    this->player.setOrigin(localBounds.left + localBounds.width/2.0f, 
                 localBounds.top  + localBounds.height/2.0f);
    this->player.setPosition(Vector2f(100.0f, 200.0f));
    sf::RectangleShape rectangle(sf::Vector2f(60, 132));
    rectangle.setOrigin(42, 65);
    rectangle.setPosition(this->player.getPosition());
    this->collisionRect = rectangle;
    this->shootingSound.loadFromFile("minigun.ogg");
    this->hurtSound.loadFromFile("hurt.flac");
    this->throwingSound.loadFromFile("Throw.wav");
    this->prevPos = Vector2f(0.f, 0.f);
    this->player.setScale(Vector2f(2.0f, 2.0f));
    this->state = movementState::Idle;
    this->lastState = movementState::Idle;
    this->onGround = true;
    this->bulletTimer.restart();
    this->shootingAnimationFinished = true;
    initAnimations();
    this->faceRight = false;
    this->jumpTimer.restart();
    this->xVel = 0;
    this->floatingBlockInteract = false;
    this->grenadeString = "./altSolider/Soldier_1/gren.png";
    this->playGrenadeAnimation = false;
    this->debugTimer.restart();
    this->tickCounter = 0;
    this->health = 30;
    this->healthStatus = healthBar(30.f, 70.f, Vector2f(this->player.getPosition().x-130, this->player.getPosition().y));
    this->debugTimer.restart();

};

Player::~Player() {
    for (bullet* b : this->bullets) {
        delete b;
    }
    this->bullets.clear();

    // No need to delete the sprites directly, as they are part of the bullet objects
    this->bulletSprites.clear();

    for (Grenade* g : this->grenades) {
        delete g;
    }
    this->grenades.clear();

    // No need to delete the sprites directly, as they are part of the grenade objects
    this->grenadeSprites.clear();
}




movementState Player::getState(){
    return this->state;
}


void Player::initAnimations(){
    this->animationTimer.restart();
}


// void Player::shootingANim

void Player::updateAnimations(){
    
    
    if(this->state == movementState::Right){
        this->player.setTexture(this->movementTexture);
        
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 896.0f){
                
                this->rect.left = 256.0f;
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
                this->rect.left = 256.0f;
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
                this->currSound.setBuffer(this->shootingSound);
                this->currSound.play();
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
        
        
    }else if(this->state == movementState::Hurt){
        this->player.setTexture(this->hurtTexture);
        
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.2f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 384.0f){  
                this->currSound.setBuffer(this->hurtSound);
                this->currSound.play();
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


    }else if(this->state == movementState::Throwing){
        
        this->player.setTexture(this->throwingTexture);
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.1f){
            this->rect.left += 128.0f;
            if(this->rect.left >= 1152.0f){  
                
                //std::cout << "Hello, world!" << std::endl;
                this->rect.left = 0.0f;
                this->state = movementState::Idle;
                this->playGrenadeAnimation = false;
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
void Player::animateIdle() {
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


void Player::groundYvalSetter(float value){
    this->groundYVal = value;
    
}


bool isColliding(const sf::Sprite& a, const sf::Sprite& b) {
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}



bool Player::isOnTopOfBlock(Sprite block) {
    // Get the bounds (i.e., the position, width, and height) of the player and block
    sf::FloatRect playerBounds = this->player.getGlobalBounds();
    sf::FloatRect blockBounds = block.getGlobalBounds();

    // Check if the player's bottom edge is intersecting with the block's top edge
    bool isAboveBlock =  (this->player.getPosition().y + this->player.getGlobalBounds().height/2) >= block.getPosition().y;
    bool isNotBelow = (this->player.getPosition().y - this->player.getGlobalBounds().height/2) <= block.getPosition().y;
    float blockTopLeft = block.getPosition().x;
    float blockTopRight = block.getPosition().x + block.getGlobalBounds().width;
    bool Horizontal = (this->player.getPosition().x >= blockTopLeft) && (this->player.getPosition().x <= blockTopRight);
    Vector2f playerHead = Vector2f(this->player.getPosition().x, this->player.getPosition().y - this->player.getGlobalBounds().height/2);
    Vector2f blockBottom = Vector2f(block.getPosition().x, block.getPosition().y + block.getGlobalBounds().height);
    // Check if the player's x coordinate is within the x boundaries of the block
    // bool isWithinBlockHorizontally = ((player.getPosition().x - (playerBounds.width/2)) >= block.getPosition().x) && (((player.getPosition().x - (playerBounds.width/2)) <= block.getPosition().x+blockBounds.width));
    
    
    
    if(isAboveBlock && Horizontal && isNotBelow){
        
        if(player.getPosition().y < block.getPosition().y){  
            player.setPosition(player.getPosition().x, block.getPosition().y - (player.getGlobalBounds().height/2));
        }
    }
    if (playerHead.y <= blockBottom.y && playerHead.x >= blockBottom.x && playerHead.x <= blockBottom.x + block.getGlobalBounds().width && this->player.getPosition().y >= blockBottom.y) {
       this->yVel = 0;

    }

    
    return isAboveBlock && Horizontal && isNotBelow;
}

//make sure to only check for bullets in a certain range
void Player::checkForBulletCollision(std::vector<bullet*> &enemyBullets){
    for(bullet *b :enemyBullets){
        if(b->sprite.getGlobalBounds().intersects(this->collisionRect.getGlobalBounds())){
            b->active = false;
            this->state = movementState::Hurt;
            if(this->damageTimer.getElapsedTime().asSeconds() >= .7f){
                this->health -= 2;
                this->damageTimer.restart();
            }
            
        }
    }
}


int Player::update(RenderWindow &win, float dt, vector<Sprite*> tiles, View currentView){
    bool keysPressed = false;
    bool playHurt = false;
    bool rightMoved = false;
    
    // Gravity always acts on the player. We'll need to check if they hit the ground later.
    // if(this->player.getPosition().y + this->player.getGlobalBounds().height  328) {
    //     this->yVel += this->gravity;
    // }
   
//    if(this->state == movementState::Hurt){
//         cout << "hurt1" << endl;
//    }
    
    
    if(!(this->onGround)){
        this->yVel += this->gravity;
       
    }else if(this->yVel >= 0 && this->state != movementState::Hurt && this->state != movementState::Throwing){
       
        this->state = movementState::Idle;
        this->yVel = 0;
        //this->player.setPosition(this->player.getPosition().x, this->groundYVal - this->player.getGlobalBounds().height/2);
        this->onGround = true;  
    }

   


    if(!this->floatingBlockInteract){
        this->xVel = 0;
    }

    if(Keyboard::isKeyPressed(Keyboard::G)){
       
        float throwSpeed = 3;
        Vector2f playerPos = this->player.getPosition();
        Vector2i mousePos = Vector2i(Mouse::getPosition(win));
        Vector2f mousePosWindow = win.mapPixelToCoords(mousePos);
        Vector2f direction = mousePosWindow - playerPos;
        if(direction.x >= 250){
            direction.x = 250;
        }
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        Vector2f throwVelocity = (direction / length) * throwSpeed;
        if(this->bulletTimer.getElapsedTime().asSeconds() >= 0.9f){
            this->currSound.setBuffer(this->throwingSound);
            this->currSound.play();
            Grenade *gren = new Grenade(this->grenadeString, 0.7, throwVelocity);
            gren->setGravity(30.f);
            gren->setInitPos(this->player.getPosition(), direction);
            this->grenades.push_back(gren);
            this->grenadeSprites.push_back(&(gren->sprite));
            this->bulletTimer.restart();
            this->state = movementState::Throwing;
            keysPressed = true;
            this->playGrenadeAnimation = true;
        }
        
        
        
    }


    if(Keyboard::isKeyPressed(Keyboard::D) && !this->playGrenadeAnimation){
        this->state = movementState::Right;
        this->prevPos = player.getPosition();
        this->collisionRect.setPosition(this->collisionRect.getPosition().x + this->movementSpeed, this->collisionRect.getPosition().y);
        bool move = true;
        for(Sprite *t : tiles){
            if(this->collisionRect.getGlobalBounds().intersects(t->getGlobalBounds()) && t->getPosition().y < this->player.getPosition().y){
                move = false;
            }
        }
        if(move){
            this->player.move(movementSpeed, 0);
            this->healthStatus.move(movementSpeed, 0);
            keysPressed = true;
            this->faceRight = true;
            updateAnimations();
            rightMoved = true;
        }else{
            this->collisionRect.setPosition(this->collisionRect.getPosition().x - this->movementSpeed, this->collisionRect.getPosition().y);
        }
    }

    

    if(Keyboard::isKeyPressed(Keyboard::A) && !this->playGrenadeAnimation){
        bool block = true;
        Sprite checkSprite = this->player;
        
        this->state = movementState::Left;
        this->prevPos = player.getPosition();
        this->collisionRect.setPosition(this->collisionRect.getPosition().x - this->movementSpeed, this->collisionRect.getPosition().y);
        bool move = true;
        for(Sprite *t : tiles){
            if(this->collisionRect.getGlobalBounds().intersects(t->getGlobalBounds()) && t->getPosition().y < this->player.getPosition().y){
                move = false;
            }
        }
        if(move){
            this->player.move(-movementSpeed, 0);
            this->healthStatus.move(-movementSpeed, 0);
            keysPressed = true;
            this->faceRight = false;
            updateAnimations();
            rightMoved = false;
        }else{
            this->collisionRect.setPosition(this->collisionRect.getPosition().x + this->movementSpeed, this->collisionRect.getPosition().y);
        }
        
    }

    

    if(Keyboard::isKeyPressed(Keyboard::Space) && this->onGround && this->jumpTimer.getElapsedTime().asSeconds() > 0.1f){
        this->prevPos = player.getPosition();
        this->state = movementState::Jumping;
        this->yVel = -this->jumpSpeed; // Set yVel to negative jumpSpeed, not subtract it
        this->jumpTimer.restart();
        
    }

   

    
    if(Mouse::isButtonPressed(Mouse::Left)){
        this->shootingAnimationFinished = false;
        std::string str = "./Bullet.png";
        this->state = movementState::Shooting;
        Vector2f playerPos = this->player.getPosition(); // get player position
        // sf::Vector2i mousePosInt = Mouse::getPosition(win); // get mouse position relative to the window
        // sf::Vector2f mousePos = win.mapPixelToCoords(mousePosInt);
        Vector2i mousePos = Vector2i(Mouse::getPosition(win));
        Vector2f mousePosWindow = win.mapPixelToCoords(mousePos);
        Vector2f aimDir = mousePosWindow - playerPos;
        float magnitude = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)); 
        Vector2f aimDirNorm;    
        
        if(magnitude != 0) {
            aimDirNorm = Vector2f(aimDir.x / magnitude, aimDir.y / magnitude);
        } else {
            aimDirNorm = Vector2f(0.f, 0.f);
        }
        keysPressed = true;
        
        updateAnimations();

        
    
        if(this->bulletTimer.getElapsedTime().asSeconds() >= 0.5f){
            this->bulletTimer.restart();
            sf::Vector2f topLeftPosition;
            topLeftPosition.x = this->player.getPosition().x - this->player.getGlobalBounds().width / 2.0f;
            topLeftPosition.y = this->player.getPosition().y - this->player.getGlobalBounds().height / 2.0f;
            bullet * sb = new bullet(str, 15.f, (aimDirNorm * 15.f)); // instantiate new bullet
            sb->sprite.setPosition(playerPos.x+64, playerPos.y - 40); // set bullet position to player position
           
            this->bulletSprites.push_back(&(sb->sprite));
            this->bulletActives.push_back(sb->active);
            this->bullets.push_back(sb); // add bullet to bullet list
        }
    }

    if(this->state == movementState::Hurt){
        updateAnimations();
        playHurt = true;
        if(this->rect.left > 384){
            this->rect.left =0;
        }
    }
    if(this->debugTimer.getElapsedTime().asSeconds() >= 0.5f){
       
       
        this->debugTimer.restart();
    }

    if(!keysPressed && !playHurt && !this->playGrenadeAnimation){
        this->state = movementState::Idle;
        animateIdle();
    }


    if(this->playGrenadeAnimation){
        updateAnimations();
    }
    
    
    for(auto it = this->bullets.begin(); it != this->bullets.end(); ) {
        (*it)->update(currentView);
        if(!(*it)->active) {
            delete *it;
            it = this->bullets.erase(it);
        } else {
            ++it;
        }
    }
    

   

    std::vector<int> inactiveIndices;

    for(int i = 0; i < this->grenades.size(); ++i){
        this->grenades[i]->update(dt, tiles);
        if(grenades[i]->state == projectileState::Inactive){
            inactiveIndices.push_back(i);
        }
    }

   

    // Remove elements from the end of the vector to the start
    for (auto it = inactiveIndices.rbegin(); it != inactiveIndices.rend(); it++ ) {
        delete this->grenades[(*it)]; // delete the Grenade object
        this->grenades.erase(this->grenades.begin() + (*it)); // erase the pointer from the vector

        // You don't need to delete the sprite separately, as it should be handled by the Grenade's destructor
        this->grenadeSprites.erase(this->grenadeSprites.begin() + (*it));
    }



        
    

    // Apply the vertical velocity to the player's position.
    player.move(0, this->yVel);
    this->healthStatus.update(this->health);
    this->healthStatus.bar.setPosition(this->player.getPosition().x-40, this->player.getPosition().y-100);
    this->healthStatus.outline.setPosition(this->player.getPosition().x-40, this->player.getPosition().y-100);
    this->collisionRect.setPosition(this->player.getPosition());
    this->tickCounter++;

    return rightMoved;

    
}



