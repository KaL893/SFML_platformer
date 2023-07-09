#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Animation.h"
#include "math.h"
#include <vector>

using namespace sf;
using namespace std;



Player::Player(){
    this->movementTexture.loadFromFile("./altSolider/Soldier_1/runTwo.png");
    this->idleTexture.loadFromFile("./altSolider/Soldier_1/IdleThree.png");
    this->shootingTexture.loadFromFile("./altSolider/Soldier_1/shooting.png");
    this->hurtTexture.loadFromFile("./altSolider/Soldier_1/hurtEdited.png");
    this->rect = IntRect(0, 0, 128, 66);
    this->player.setTexture(this->idleTexture);
    this->player.setTextureRect(this->rect);
    this->gravity = 0.5f;
    this->jumpSpeed = 15.0f;
    this->yVel = 0.0f;
    sf::FloatRect localBounds = player.getLocalBounds();
    sf::IntRect rect = player.getTextureRect();
    
    std::cout << "Rectangle Dimensions: " << "Width: " << rect.width << ", Height: " << rect.height << std::endl;
    
    
// Set the origin of your sprite to its center
    this->player.setOrigin(localBounds.left + localBounds.width/2.0f, 
                 localBounds.top  + localBounds.height/2.0f);
    this->player.setPosition(Vector2f(100.0f, 200.0f));
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
    

};

Player::~Player(){
    for(bullet *b : this->bullets){
        delete b;
    }
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
    // Check if the player's x coordinate is within the x boundaries of the block
    // bool isWithinBlockHorizontally = ((player.getPosition().x - (playerBounds.width/2)) >= block.getPosition().x) && (((player.getPosition().x - (playerBounds.width/2)) <= block.getPosition().x+blockBounds.width));
    
    if(isAboveBlock && Horizontal && isNotBelow){
        if(player.getPosition().y < block.getPosition().y){
            player.setPosition(player.getPosition().x, block.getPosition().y - (player.getGlobalBounds().height/2));
        }
    }
    
    return isAboveBlock && Horizontal && isNotBelow;
}

//make sure to only check for bullets in a certain range
void Player::checkForBulletCollision(std::vector<bullet*> &enemyBullets){
    for(bullet *b :enemyBullets){
        if(b->sprite.getGlobalBounds().intersects(this->player.getGlobalBounds())){
            this->state = movementState::Hurt;
            
        }
    }
}


int Player::update(RenderWindow &win, float dt){
    bool keysPressed = false;
    bool playHurt = false;
    
    // Gravity always acts on the player. We'll need to check if they hit the ground later.
    // if(this->player.getPosition().y + this->player.getGlobalBounds().height  328) {
    //     this->yVel += this->gravity;
    // }
   
//    if(this->state == movementState::Hurt){
//         cout << "hurt1" << endl;
//    }
    
    if(!(this->onGround)){
        this->yVel += this->gravity;
    }else if(this->yVel >= 0 && this->state != movementState::Hurt){
       
        this->state = movementState::Idle;
        this->yVel = 0;
        //this->player.setPosition(this->player.getPosition().x, this->groundYVal - this->player.getGlobalBounds().height/2);
        this->onGround = true;  
    }

   
   

    if(!this->floatingBlockInteract){
        this->xVel = 0;
    }

    if(Keyboard::isKeyPressed(Keyboard::D)){
        this->state = movementState::Right;
        this->prevPos = player.getPosition();
        this->player.move(movementSpeed, 0);
        keysPressed = true;
        this->faceRight = true;
        updateAnimations();
        
    }

    if(Keyboard::isKeyPressed(Keyboard::A)){ 
        this->state = movementState::Left;
        this->prevPos = player.getPosition();
        this->player.move(-movementSpeed, 0);
        keysPressed = true;
        updateAnimations();
        this->faceRight = false;
        
    }

    if(Keyboard::isKeyPressed(Keyboard::Space) && this->onGround && this->jumpTimer.getElapsedTime().asSeconds() > 0.1f){
        this->prevPos = player.getPosition();
        this->state = movementState::Jumping;
        this->yVel = -this->jumpSpeed; // Set yVel to negative jumpSpeed, not subtract it
        this->jumpTimer.restart();
        
    }

    if(Keyboard::isKeyPressed(Keyboard::G) && this->bulletTimer.getElapsedTime().asSeconds() >= 0.5f){
        float throwSpeed = 3;
        Vector2f playerPos = this->player.getPosition(); // get player position
        // sf::Vector2i mousePosInt = Mouse::getPosition(win); // get mouse position relative to the window
        // sf::Vector2f mousePos = win.mapPixelToCoords(mousePosInt);
        Vector2i mousePos = Vector2i(Mouse::getPosition(win));
        Vector2f mousePosWindow = win.mapPixelToCoords(mousePos);
        Vector2f direction = mousePosWindow - playerPos;


        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        Vector2f throwVelocity = (direction / length) * throwSpeed;
        // Grenade *gren = new Grenade()
        Grenade *gren = new Grenade(this->grenadeString, 0.7, throwVelocity);
        gren->setGravity(10.f);
        gren->setInitPos(this->player.getPosition(), direction);
        this->grenades.push_back(gren);
        this->bulletTimer.restart();
        this->state = movementState::Thr
        keysPressed = true;
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

    if(!keysPressed && !playHurt){
        this->state = movementState::Idle;
        animateIdle();
    }
    // if(this->state == movementState::Hurt){
    //     cout << "hurt3" << endl;
    // }
    

    //std::cout << this->state << endl; 
    
    for(bullet *b:this->bullets){
        b->update();
    }

    for(Grenade *g:this->grenades){
        g->update(dt);
    }

    // Apply the vertical velocity to the player's position.
    player.move(0, this->yVel);

    

    if(keysPressed){
        return 1;
    }else{
        return 0;
    }

    
}



