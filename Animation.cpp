// #include <iostream>
// #include <SFML/Graphics.hpp>
// using namespace sf;
// #include "Animation.h"



// Animation::Animation(Texture textureSheet, int imageCount,Vector2f imageDimensions,float switchTime){
//     this->imageCount = imageCount;
//     this->switchTime = switchTime;
//     this->imageDimensions = imageDimensions;
//     this->maxFrameCoord = this->imageDimensions.x * (this->imageCount-1);
//     this->uvRect = IntRect(0, 0, this->imageDimensions.x, this->imageDimensions.y);
//     this->animationClock.restart();
//     this->textureSheet = textureSheet;
// }

// Animation::~Animation(){}

// void Animation::update(Sprite &playerSprite, movementState state){
    
//     if(state == movementState::Right){
//         std::cout << "Here" << std::endl;
//         // Do some stuff
//         if(this->animationClock.getElapsedTime().asSeconds() >= this->switchTime){
//             this->uvRect.left += this->imageDimensions.x;
//             if(this->uvRect.left >= this->maxFrameCoord){
//                 this->uvRect.left = 0.0f;
//             }
//             this->animationClock.restart();
//         }
//         playerSprite.setTextureRect(this->uvRect);
//         std::cout << "Left " << this->uvRect.left << std::endl;
//         playerSprite.setScale(Vector2f(2.0f, 2.0f));
//     }else if(state == movementState::Left){
//         // Do some other stuff
//         if(this->animationClock.getElapsedTime().asSeconds() >= this->switchTime){
//             this->uvRect.left += this->imageDimensions.x;
//             if(this->uvRect.left >= this->maxFrameCoord){
//                 this->uvRect.left = 0.0f;
//             }
//             this->animationClock.restart();
//         }
//         playerSprite.setTextureRect(this->uvRect);
//         playerSprite.setScale(Vector2f(-2.0f, -2.0f));
//     }else if(state == movementState::Idle){
        
//     }
// }


    




