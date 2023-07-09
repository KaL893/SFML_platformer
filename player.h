#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Animation.h"
#include "entityStates.h"
#include "bullet.h"
#include "Grenade.h"
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H
using namespace std;

class Player {
private:
    Texture movementTexture;
    Sprite selfSprite;
    Texture idleTexture;
    Texture shootingTexture;
    Texture hurtTexture;
    unsigned int row;
    //Animation Animation;
    Clock animationTimer;
    Clock jumpTimer;
    IntRect rect;
    movementState state;
    movementState lastState;
    float yVel;
    float gravity;
    float jumpSpeed;
    void groundColCheck();
    float groundYVal;
    Event mouseClick;
    Clock bulletTimer;
    bool shootingAnimationFinished;
    bool faceRight;

    Vector2f prevPos;
    string grenadeString;
    
    
    //vector<floatingTile*> floatingTiles;

        


public:
    bool floatingBlockInteract;
    bool onFloatingBlock;
    int xVel;
    bool onGround;
    bool isOnTopOfBlock(Sprite block);
    Player();
    ~Player();
    std::vector<bullet*> bullets;
    vector<Grenade*> grenades;
    int movementSpeed = 5;
    Sprite player;
    Sprite idleSprite;
    int update(RenderWindow& win, float dt);
    void Draw(RenderWindow window);
    void animateRight();
    void setValues();
    void updateAnimations();
    void initAnimations();
    void animateIdle();
    void animateShooting();
    movementState getState();
    void groundYvalSetter(float value);
    void checkForBulletCollision(vector<bullet*> &enemyBullets);

    

    bool last = true;
    

    
    
};



#endif /* PLAYER_H */