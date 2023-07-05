
#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
using namespace sf;
#ifndef GAMEBLOCK_H
#define GAMEBLOCK_H

class gameBlock{
    public:
        Texture texture;
        Vector2f coordinates;
        Sprite block;
        IntRect rect;
    
        gameBlock();
        ~gameBlock();
        
    private:
        void checkPlayerCollisions(Player player);

};

#endif