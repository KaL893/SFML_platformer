#include <iostream>
#include "Parralax.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
Parralax::Parralax(float playerMovementSpeed){
    // Load the textures
    this->layer2.loadFromFile("./Layers/bg_forest_close.png");
    this->layer3.loadFromFile("./Layers/bg_forest_far.png");
    this->layer4.loadFromFile("./Layers/bg_forest_middle.png");
    this->layer5.loadFromFile("./Layers/bg_mountains.png");
    this->layer6.loadFromFile("./Layers/bg_sky.png");
    this->sprite1.setTexture(this->layer1);
    this->sprite2.setTexture(this->layer2);
    this->sprite3.setTexture(this->layer3);
    this->sprite4.setTexture(this->layer4);
    this->sprite5.setTexture(this->layer5);
    this->sprite6.setTexture(this->layer6);
    this->sprite1b.setTexture(this->layer1);
    this->sprite2b.setTexture(this->layer2);
    this->sprite3b.setTexture(this->layer3);
    this->sprite4b.setTexture(this->layer4);
    this->sprite5b.setTexture(this->layer5);
    this->sprite6b.setTexture(this->layer6);
    this->sprite1.setPosition(0,0);
    this->sprite1b.setPosition(272,0);
    this->sprite2.setPosition(0,0);
    this->sprite2b.setPosition(272,0);
    this->sprite3.setPosition(0,0);
    this->sprite3b.setPosition(272,0);
    this->sprite4.setPosition(0,0);
    this->sprite4b.setPosition(272,0);
    this->sprite5.setPosition(0,0);
    cout << this->sprite5.getGlobalBounds().left + this->sprite5.getGlobalBounds().width << endl;
    this->sprite5b.setPosition(272,0);
    cout << this->sprite5b.getGlobalBounds().left + this->sprite5b.getGlobalBounds().width << endl;
    this->sprite6.setPosition(0,0);
    this->sprite6b.setPosition(272,0);
    this->activeX = true;
    // Resize the sprites
    
    
    
    

    // this->layerThree.setScale((desiredWidth-100) / spriteSize.x, (desiredHeight-100) / spriteSize.y);
    
    
    // this->layerTwo.setScale((desiredWidth-60) / spriteSize.x, (desiredHeight-100) / spriteSize.y);
    
    
    // this->layerOne.setScale(desiredWidth / spriteSize.x, (desiredHeight-600) / spriteSize.y);
    
    // Set movement speed
   



    
}



Parralax::~Parralax(){}

void Parralax::render(RenderWindow &window){
    window.draw(this->sprite6);
    window.draw(this->sprite6b);
    window.draw(this->sprite5);
    window.draw(this->sprite5b);
    window.draw(this->sprite4);
    window.draw(this->sprite4b);
    window.draw(this->sprite3);
    window.draw(this->sprite3b);
    window.draw(this->sprite1);
    window.draw(this->sprite1b);
    window.draw(this->sprite2);
    window.draw(this->sprite2b);
}

void Parralax::update(bool playerMoved, View view){
    if(playerMoved){
            this->sprite1.move(-1, 0);
            this->sprite1b.move(-1, 0);
            this->sprite2.move(-0.8, 0);
            this->sprite2b.move(-0.8, 0);
            this->sprite3.move(-0.6, 0);
            this->sprite3b.move(-0.6, 0);
            this->sprite4.move(-0.4, 0);
            this->sprite4b.move(-0.4, 0);
            this->sprite5.move(-0.3, 0);
            this->sprite5b.move(-0.3, 0);
            this->sprite6.move(-0.2, 0);
            this->sprite6b.move(-0.2, 0);
            
            // std::cout << this->sprite3.getPosition().x << ", " << this->sprite3.getPosition().y << std::endl;
            // std::cout << this->sprite3b.getPosition().x << ", " << this->sprite3b.getPosition().y << std::endl;
            float viewLeftEdge =  view.getCenter().x - (view.getSize().x / 2.0f);

            // repositioning sprites
            if (this->sprite1.getGlobalBounds().left + this->sprite1.getGlobalBounds().width < viewLeftEdge) {
                this->sprite1.setPosition(this->sprite1b.getGlobalBounds().left + this->sprite1b.getGlobalBounds().width, 0);
               
            }
            if (this->sprite1b.getGlobalBounds().left + this->sprite1b.getGlobalBounds().width < viewLeftEdge) {
                this->sprite1b.setPosition(this->sprite1.getGlobalBounds().left + this->sprite1.getGlobalBounds().width, 0);
               
            }

            if (this->sprite2.getGlobalBounds().left + this->sprite2.getGlobalBounds().width < viewLeftEdge) {
                this->sprite2.setPosition(this->sprite2b.getGlobalBounds().left + this->sprite2b.getGlobalBounds().width, 0);
            }
            if (this->sprite2b.getGlobalBounds().left + this->sprite2b.getGlobalBounds().width < viewLeftEdge) {
                this->sprite2b.setPosition(this->sprite2.getGlobalBounds().left + this->sprite2.getGlobalBounds().width, 0);
            }

            if (this->sprite3.getGlobalBounds().left + this->sprite3.getGlobalBounds().width < viewLeftEdge) {
                this->sprite3.setPosition(this->sprite3b.getGlobalBounds().left + this->sprite3b.getGlobalBounds().width, 0);
                // std::cout << "\nhere1" << std::endl;
            }
            if (this->sprite3b.getGlobalBounds().left + this->sprite3b.getGlobalBounds().width < viewLeftEdge) {
                this->sprite3b.setPosition(this->sprite3.getGlobalBounds().left + this->sprite3.getGlobalBounds().width, 0);
                //std::cout << "\nhere2" << std::endl;
            }

            if (this->sprite4.getGlobalBounds().left + this->sprite4.getGlobalBounds().width < viewLeftEdge) {
                this->sprite4.setPosition(this->sprite4b.getGlobalBounds().left + this->sprite4b.getGlobalBounds().width, 0);
            }
            if (this->sprite4b.getGlobalBounds().left + this->sprite4b.getGlobalBounds().width < viewLeftEdge) {
                this->sprite4b.setPosition(this->sprite4.getGlobalBounds().left + this->sprite4.getGlobalBounds().width, 0);
            }

            if (this->sprite5.getGlobalBounds().left + this->sprite5.getGlobalBounds().width < viewLeftEdge) {
                // std::cout << this->sprite5.getPosition().x << ", " << this->sprite5.getPosition().y << std::endl;
                // std::cout << this->sprite5b.getPosition().x << ", " << this->sprite5b.getPosition().y << std::endl;
                this->sprite5.setPosition(this->sprite5b.getGlobalBounds().left + this->sprite5b.getGlobalBounds().width, 0);
                // std::cout << this->sprite5.getPosition().x << ", " << this->sprite5.getPosition().y << std::endl;
                // std::cout << this->sprite5b.getPosition().x << ", " << this->sprite5b.getPosition().y << std::endl;
                
            }
            if (this->sprite5b.getGlobalBounds().left + this->sprite5b.getGlobalBounds().width < viewLeftEdge) {
                this->sprite5b.setPosition(this->sprite5.getGlobalBounds().left + this->sprite5.getGlobalBounds().width, 0);
                
            }

            if (this->sprite6.getGlobalBounds().left + this->sprite6.getGlobalBounds().width < viewLeftEdge) {
                this->sprite6.setPosition(this->sprite6b.getGlobalBounds().left + this->sprite6b.getGlobalBounds().width, 0);
                
            }
            if (this->sprite6b.getGlobalBounds().left + this->sprite6b.getGlobalBounds().width < viewLeftEdge) {
                this->sprite6b.setPosition(this->sprite6.getGlobalBounds().left + this->sprite6.getGlobalBounds().width, 0);
                
            }
            
            

        }
        


}

