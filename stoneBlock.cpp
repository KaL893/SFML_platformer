
#include <iostream>
#include <SFML/Graphics.hpp>
#include "stoneBlock.h"


stoneBlock::stoneBlock(){
    this->texture.loadFromFile("./wallTextures/Stone/Stones.png");
    this->rect = IntRect(0, 0, 128, 128);
    this->block.setTexture(this->texture);
    this->block.setTextureRect(this->rect);
}