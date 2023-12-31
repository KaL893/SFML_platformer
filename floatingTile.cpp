#include "floatingTile.h"
using namespace sf;

floatingTile::floatingTile(float lowerBound, float upperBound,bool xMoving,float yVal ,Texture blockTexture, float movementSpeed){
    this->movementRange = Vector2f(lowerBound, upperBound);
    this->xMoving = xMoving;
    this->texture = blockTexture;
    this->block.setTexture(this->texture);
    IntRect rect(0, 0, 64, 64);
    this->block.setTextureRect(rect);
    this->block.setPosition(this->movementRange.x, yVal);
    
    this->movementSpeed = movementSpeed;
    this->playerOnTop = false;
    this->vel = 1;
    
}


void floatingTile::update(Sprite *player, RectangleShape* bar, RectangleShape* outline){
    if(this->xMoving){
        if(this->block.getPosition().x <= this->movementRange.x){
            this->vel = 1;
        }else if(this->block.getPosition().x >= this->movementRange.y){
            this->vel = -1;
        }
    }
    
    this->block.move(this->movementSpeed * this->vel, 0);
    if(this->playerOnTop){
        player->move(this->movementSpeed * this->vel, 0);
        bar->move(this->movementSpeed*this->vel, 0);
        outline->move(this->movementSpeed*this->vel, 0);
    }

}