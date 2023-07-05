#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Animation.h"
#include "entityStates.h"
#include "bullet.h"
#include <vector>

class Enemy{

    private:
        Texture movementTexture;
        
        Texture idleTexture;
        Texture shootingTexture;
        unsigned int row;
        //Animation Animation;
        Clock animationTimer;
        IntRect rect;
        movementState state;
        movementState lastState;
        float yVel;
        float gravity;
        float jumpSpeed;
        bool onGround;
        void groundColCheck();
        float groundYVal;
        Event mouseClick;
        Clock bulletTimer;
        bool shootingAnimationFinished;
        int shootCount;
        int frames;
        bool faceRight;
        void initAnimations(); // Should be an abstract method
        void updateAnimations();
        void animateIdle();
        int movementDirection;
        int movementSpeed;


    public:
        Vector2f movementRange;
        Sprite player;
        Enemy();
        ~Enemy();
        void update();


    
};