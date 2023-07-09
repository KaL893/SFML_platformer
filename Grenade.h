#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
using namespace sf;


// Bullet.h
#ifndef GRENADE_H
#define GRENADE_H

#include "Projectile.h"

class Grenade : public Projectile {

private:
    float gravity;
    Vector2f initialPos;
    Vector2f direction;
public:
    Grenade(std::string& str, float movementSpeed, Vector2f velocity); // Constructor declaration
    ~Grenade(); // Destructor declaration
    void setGravity(float gravity);
    void setInitPos(Vector2f initialPos, Vector2f direction);
    void update(float dt);

};

#endif //Grenade.h


