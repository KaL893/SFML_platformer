// #include <iostream>
// #include <SFML/Graphics.hpp>
// using namespace sf;
// #include "Animation.h"


// Animation::Animation(Texture *Texture, Vector2u imageCount, float switchTime){
//     this->imageCount = imageCount;
//     this->switchTime = switchTime;
//     totalTime = 0.0f;
//     currImage.x = 0;
//     uvRect.width = 128;
//     uvRect.height = 116;
// }

// void Animation::update(int row, float deltaTime, bool faceRight){
//     currImage.y = row;
//     totalTime += deltaTime;
//     if(totalTime >= deltaTime){
//         totalTime -= switchTime;
//         currImage.x++;
//     }

//     if(currImage.x >= imageCount.x){
//         currImage.x = 0;
//     }
//     uvRect.left = currImage.x * uvRect.width;
//     uvRect.top = currImage.y * uvRect.height;


// } 

