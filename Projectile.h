
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;



#ifndef PROJECTILE_H
#define PROJECTILE_H
class Projectile{

    protected:
        Texture texture;
        Vector2f velocity;
        float movementSpeed;
        
    public:
        bool active;
        Sprite sprite;
        Projectile(std::string& str, float movementSpeed, Vector2f velocity);
        virtual ~Projectile();
        virtual void update(View currentView);




};

#endif 