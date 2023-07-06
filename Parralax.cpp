#include <iostream>
#include "Parralax.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Parralax::Parralax(float playerMovementSpeed){
    // Load the textures
    this->layerFourTexture.loadFromFile("./layers/l4.png");
    this->layerThreeTexture.loadFromFile("./layers/l3.png");
    this->layerTwoTexture.loadFromFile("./layers/l2.png");
    this->layerOneTexture.loadFromFile("./layers/l1.png");

    // Set the textures
    this->layerFour.setTexture(this->layerFourTexture);
    this->layerThree.setTexture(this->layerThreeTexture);
    this->layerTwo.setTexture(this->layerTwoTexture);
    this->layerOne.setTexture(this->layerOneTexture);

    // Resize the sprites
    float desiredWidth = 1360.0f;
    float desiredHeight = 1200.0f;

    
        
    
    this->layerFour.setScale(6.0f, 6.0f);
    this->layerThree.setScale(7.0f, 6.0f);
    this->layerTwo.setScale(6.0f, 6.0f);    
    this->layerOne.setScale(5.0f, 5.0f);


    this->layerFourB.setTexture(this->layerFourTexture);
    this->layerThreeB.setTexture(this->layerThreeTexture);
    this->layerTwoB.setTexture(this->layerTwoTexture);
    this->layerOneB.setTexture(this->layerOneTexture);

    // Resize the sprites
    

    
        
    
     this->layerFourB.setScale(6.0f, 6.0f);
     this->layerThreeB.setScale(7.0f, 6.0f);
     this->layerTwoB.setScale(6.0f, 6.0f);
     this->layerOneB.setScale(5.0f, 5.0f);


    // this->layerThree.setScale((desiredWidth-100) / spriteSize.x, (desiredHeight-100) / spriteSize.y);
    
    
    // this->layerTwo.setScale((desiredWidth-60) / spriteSize.x, (desiredHeight-100) / spriteSize.y);
    
    
    // this->layerOne.setScale(desiredWidth / spriteSize.x, (desiredHeight-600) / spriteSize.y);
    
    // Set movement speed
    this->playerMovementSpeed = 1;
    this->layerOneMovementSpeed = 0.8f ;
    this->layerTwoMovementSpeed = 0.6f ;
    this->layerThreeMovementSpeed = 0.4f;
    this->layerFourMovementSpeed = 0.2f;




    
}

void Parralax::setTopLeftCoordinates(Vector2f topLeft){
    this->viewTopLeft = topLeft;
    this->layerFour.setPosition(-680, -500);
    this->layerFourB.setPosition(this->layerFour.getGlobalBounds().width - 680, -500);
    this->layerThree.setPosition(-680, -500);
    this->layerThreeB.setPosition(this->layerThree.getGlobalBounds().width - 680, -500);
    this->layerTwo.setPosition(-680, -500);
    this->layerTwoB.setPosition(this->layerTwo.getGlobalBounds().width - 680, -500);
    this->layerOne.setPosition(-680, -100);
    this->layerOneB.setPosition(this->layerOne.getGlobalBounds().width - 680, -100); 
}

Parralax::~Parralax(){}

void Parralax::render(RenderWindow &window){
    window.draw(this->layerFourB);
    window.draw(this->layerFour);
    window.draw(this->layerThree);
    window.draw(this->layerThreeB);
    window.draw(this->layerTwoB);
    window.draw(this->layerTwo);
    window.draw(this->layerOne);
    window.draw(this->layerOneB);
}

void Parralax::update(bool playerMoved, View view){
    if(playerMoved){
        this->layerOne.move(-this->layerOneMovementSpeed, 0);
        this->layerTwo.move(-this->layerTwoMovementSpeed, 0);
        this->layerThree.move(-this->layerThreeMovementSpeed, 0);
        this->layerFour.move(-this->layerFourMovementSpeed, 0);
        this->layerOneB.move(-this->layerOneMovementSpeed, 0);
        this->layerTwoB.move(-this->layerTwoMovementSpeed, 0);
        this->layerThreeB.move(-this->layerThreeMovementSpeed, 0);
        this->layerFourB.move(-this->layerFourMovementSpeed, 0);

        float viewLeftEdge = view.getCenter().x - (view.getSize().x / 2.0f);

                // Example for layer one
        if (this->layerOne.getGlobalBounds().left + this->layerOne.getGlobalBounds().width < viewLeftEdge) {
            this->layerOne.setPosition(this->layerOneB.getGlobalBounds().left + this->layerOneB.getGlobalBounds().width, -100);
        }
        if (this->layerOneB.getGlobalBounds().left + this->layerOneB.getGlobalBounds().width < viewLeftEdge) {
            this->layerOneB.setPosition(this->layerOne.getGlobalBounds().left + this->layerOne.getGlobalBounds().width, -100);
        }


        if (this->layerTwo.getGlobalBounds().left + this->layerTwo.getGlobalBounds().width < viewLeftEdge) {
            this->layerTwo.setPosition(this->layerTwoB.getGlobalBounds().left + this->layerTwoB.getGlobalBounds().width, -500);
        }
        if (this->layerTwoB.getGlobalBounds().left + this->layerTwoB.getGlobalBounds().width < viewLeftEdge) {
            this->layerTwoB.setPosition(this->layerTwo.getGlobalBounds().left + this->layerTwo.getGlobalBounds().width, -500);
        }

        if (this->layerThree.getGlobalBounds().left + this->layerThree.getGlobalBounds().width < viewLeftEdge) {
            this->layerThree.setPosition(this->layerThreeB.getGlobalBounds().left + this->layerThreeB.getGlobalBounds().width, -500);
        }
        if (this->layerThreeB.getGlobalBounds().left + this->layerThreeB.getGlobalBounds().width < viewLeftEdge) {
            this->layerThreeB.setPosition(this->layerThree.getGlobalBounds().left + this->layerThree.getGlobalBounds().width, -500);
        }

        if (this->layerFour.getGlobalBounds().left + this->layerFour.getGlobalBounds().width < viewLeftEdge) {
            this->layerFour.setPosition(this->layerFourB.getGlobalBounds().left + this->layerFourB.getGlobalBounds().width, -500);
        }
        if (this->layerFourB.getGlobalBounds().left + this->layerFourB.getGlobalBounds().width < viewLeftEdge) {
            this->layerFourB.setPosition(this->layerFour.getGlobalBounds().left + this->layerFour.getGlobalBounds().width, -500);
        }


        // Example for layer one



        
        


    }
}
