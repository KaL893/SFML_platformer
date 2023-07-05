#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "Animation.h"
#include "math.h"
using namespace sf;
class Movable{
    public:
        Movable();
        ~Movable();
        std::vector<bullet*> bullets;
        int movementSpeed = 5;
        Sprite player;
        Sprite idleSprite;
        int update(RenderWindow& win);
        void Draw(RenderWindow window);


    private:
        IntRect rect;
        Texture movementTexture;
        
        Texture idleTexture;
        Texture shootingTexture;
        
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


}