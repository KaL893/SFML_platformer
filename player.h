#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Animation.h"
#include "entityStates.h"
#include "bullet.h"
#include "Grenade.h"

#include <vector>
#include <SFML/Audio.hpp>
#include "healthBar.h"
#ifndef PLAYER_H
#define PLAYER_H
using namespace std;
using namespace sf;
class Player {
private:
    Texture movementTexture;
    Sprite selfSprite;
    Texture idleTexture;
    Texture shootingTexture;
    Texture hurtTexture;
    Texture throwingTexture;
    unsigned int row;
    //Animation Animation;
    Clock animationTimer;
    Clock jumpTimer;
    IntRect rect;
    float yVel;
    float gravity;
    float jumpSpeed;
    void groundColCheck();
    float groundYVal;
    Event mouseClick;
    Clock bulletTimer;
    Clock debugTimer;
    bool shootingAnimationFinished;
    bool faceRight;
    bool playGrenadeAnimation;
    Vector2f prevPos;
    string grenadeString;
    int tickCounter;
    int debugCounter = 0;
    SoundBuffer shootingSound;
    SoundBuffer hurtSound;
    SoundBuffer throwingSound;
    Sound currSound;
    
    //vector<floatingTile*> floatingTiles;

        


public:
    float health;
    movementState lastState;
    movementState state;
    Clock damageTimer;
    Clock healthBarShow;
    healthBar healthStatus;
    RectangleShape collisionRect;
    bool floatingBlockInteract;
    bool onFloatingBlock;
    int xVel;
    bool onGround;
    bool isOnTopOfBlock(Sprite block);
    Player();
    ~Player();
    std::vector<bullet*> bullets;
    std::vector<Sprite*> bulletSprites;
    std::vector<bool> bulletActives;
    vector<Grenade*> grenades;
    std::vector<Sprite*> grenadeSprites;
    int movementSpeed = 5;
    Sprite player;
    Sprite idleSprite;
    int update(RenderWindow& win, float dt, vector<Sprite*> tiles, vector<Sprite*> spikes, View currentView);
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
    bool isJumping;
    float yLvlBeforeJumping;

    

    bool last = true;
    

    
    
};



#endif /* PLAYER_H */