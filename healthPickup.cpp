#include "healthPickup.h"

healthPickup::healthPickup(){
    this->texture.loadFromFile("./pickups.png");
    this->rect = IntRect(0, 0, 24, 24);
    this->block.setTexture(this->texture);
    this->block.setTextureRect(this->rect);
    this->direction = -1;
    this->tally = 0;
    this->movementIncrements = 0.25f;
}


void healthPickup::update(){
    if(this->tally == 2){
        this->tally = 0;
        this->direction *= -1;
    }
    this->block.move(this->block.getPosition().x, this->direction * this->movementIncrements);
    cout << this->block.getPosition().y << endl;
    this->tally += this->movementIncrements;
    
    
}