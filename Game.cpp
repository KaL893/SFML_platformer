#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace std;


Game::Game(){
    width = 1200;
    height = 1200;
    fps = 60;
    title = "SFML Pong game";
    initWindow();
    
}


void Game::initWindow(){ 
    window = new RenderWindow(VideoMode(width, height), title);
    window->setFramerateLimit(fps);
    running = true;
    
}

Game::~Game(){
    delete window;
}


void Game::pollEvents(){
    while (window->pollEvent(ev)){
        if(ev.type == Event::Closed){
            window->close();
            running = false;
        }
    }
}


void Game::render(){
    window->clear();
    window->draw(playerOne.player);
    window->display();
}

void Game::update(){
    bool keysPressed = false;
    if(Keyboard::isKeyPressed(Keyboard::Right)){
        cout << "Dawg" << endl;
        playerOne.moving = true;
        playerOne.player.move(playerOne.movementSpeed, 0);
        keysPressed = true;
        playerOne.updateAnimations();
    }

    if(Keyboard::isKeyPressed(Keyboard::Left)){
        playerOne.player.move(playerOne.movementSpeed, 0);
        keysPressed = true;
    }

    if(!keysPressed){
        playerOne.moving = false;
        playerOne.animateIdle();
    }


}
