#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Animation.h"
#ifndef PLAYER_H
#define PLAYER_H


class Player {
private:
    Texture curTexture;
    Sprite selfSprite;
    Texture idleTexture;
    RectangleShape body;
    unsigned int row;
    //Animation Animation;
    Clock animationTimer;
    IntRect rect;


public:
    Player();
    ~Player();
    int movementSpeed = 5;
    Sprite player;
    Sprite idleSprite;
    void update();
    void Draw(RenderWindow window);
    bool moving = false;
    bool faceRight;
    void animateRight();
    void setValues();
    void updateAnimations();
    void initAnimations();
    void animateIdle();
    


    bool last = true;
    

    
    
};



#endif /* PLAYER_H */