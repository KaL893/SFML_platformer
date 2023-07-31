#include <iostream>
#include <SFML/Graphics.hpp>
#include "Spikes.h"


Spikes::Spikes(){
    this->texture.loadFromFile("./wallTextures/spikes.png");
    this->rect = IntRect(0, 0, 16, 16);
    this->block.setTexture(this->texture);
    this->block.setTextureRect(this->rect);
    this->block.setScale(4, 4);
}