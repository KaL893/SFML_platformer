#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <SFML/Audio.hpp>
#include "entityStates.h"
using namespace sf;
using namespace std;


// Bullet.h
#ifndef GRENADE_H
#define GRENADE_H

#include "Projectile.h"



class Grenade : public Projectile {

private:
    float gravity;
    Vector2f initialPos;
    Vector2f direction;
    Clock animationTimer;
    Texture explosionTexture;
    IntRect rect;
    Clock debugClock;
    Clock timeSinceThrow;
    Sprite collisionSprite;
    SoundBuffer explosionSound;
    Sound currSound;
    bool explosionPlayed;
    bool collided;
    void animateExplosion();
    
public:
    projectileState state;
    Grenade(std::string& str, float movementSpeed, Vector2f velocity); // Constructor declaration
    ~Grenade(); // Destructor declaration
    void setGravity(float gravity);
    void setInitPos(Vector2f initialPos, Vector2f direction);
    void update(float dt, vector<Sprite*> blocks);
    

};

#endif //Grenade.h


