
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;



#ifndef PROJECTILE_H
#define PROJECTILE_H
class Projectile{

    private:
        Texture texture;
        Vector2f velocity;
        bool active;
        float movementSpeed;
        
    public:
        Sprite sprite;
        Projectile(std::string& str, float movementSpeed, Vector2f velocity);
        ~Projectile();
        void update();




};

#endif 