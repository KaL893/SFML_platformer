
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tile.h"


Tile::Tile(){
    this->texture.loadFromFile("./wallTextures/Tile/Tiles.png");
    this->rect = IntRect(0, 0, 128, 128);
    this->block.setTexture(this->texture);
    this->block.setTextureRect(this->rect);
    this->block.setScale(0.5f, 0.5f);
}