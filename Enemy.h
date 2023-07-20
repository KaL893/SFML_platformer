#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Animation.h"
#include "entityStates.h"
#include "bullet.h"
#include <vector>
#include "healthBar.h"
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;
class Enemy{

    private:
        Texture movementTexture;
        Texture hurtTexture;
        Texture idleTexture;
        Texture shootingTexture;
        Texture dyingTexture;
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
        bool shootingFinished;
        movementState pastState;
        Clock shootingAnimationTimer;
        Clock hurtAnimationTimer;
        bool hurtAnimationFinished;
        bool invincible;
        SoundBuffer shootingSound;
        SoundBuffer hurtSound;
        Sound currSound;
        RectangleShape collisionRect;



    public:
        bool active = true;
        Clock damageTimer;
        float health;
        healthBar healthStatus;
        vector<bullet*> bullets;
        
        Vector2f movementRange;
        Sprite player;
        Enemy();
        ~Enemy();
        void update(Sprite *playerSprite, vector<bullet*> playerBullets, vector<Sprite*> playerGrenadeSprites, View currentView);
        void shoot();
        void render(RenderWindow *target);


    
};