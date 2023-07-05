#include <iostream>
#include <SFML/Graphics.hpp>
#include "bullet.h"
using namespace sf;





// Bullet.cpp
#include "bullet.h"

// Constructor implementation
bullet::bullet(std::string& str, float movementSpeed, Vector2f velocity)
    : Projectile(str, movementSpeed, velocity) {
    // Additional initialization here.
}

// Destructor implementation
bullet::~bullet() {
    // Additional cleanup here.
}
