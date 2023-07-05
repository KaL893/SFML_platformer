#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
using namespace sf;


// Bullet.h
#ifndef BULLET_H
#define BULLET_H

#include "Projectile.h"

class bullet : public Projectile {
public:
    bullet(std::string& str, float movementSpeed, Vector2f velocity); // Constructor declaration

    ~bullet(); // Destructor declaration
};

#endif // BULLET_H
