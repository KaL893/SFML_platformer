#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "bullet.h"
#include "string"
#include <fstream>
#include <string>
using namespace std;


Game::Game() : background(5.0f)
{
    this->width = 1280;
    this->height = 1280;
    this->fps = 60;
    title = "";
    this->initialBlockY = 328.f;
    float value;
    
    
    // for(int i = 0; i < 20; i++){
    //     Tile* sb = new Tile();
    //     sb->coordinates = Vector2f( i*64 , this->initialBlockY);
    //     sb->block.setPosition(sb->coordinates);
    //     this->tiles.push_back(sb);

    //     value = sb->block.getPosition().y;
    // }

    this->gameLevel = 1;
    snprintf(this->levelString, sizeof(this->levelString), "Level%d.txt", this->gameLevel);
    this->testTexture.loadFromFile("./wallTextures/Stone/Stones.png");
    this->testTile = new floatingTile(1270.f, 1472.f, true, value, testTexture, 2);
    std::string line;
    std::ifstream file(this->levelString);       
    // for(int i = 0; )
    int yLvl = 0;
    int xlvl;
   
    while(std::getline(file, line)){
        xlvl = 0;
        for(char& c : line) {
            // Now 'c' is the character in the line.
            std::cout << c;
            if(c == '='){
                Tile *sb = new Tile();
                sb->coordinates = Vector2f(xlvl, yLvl);
                sb->block.setPosition(sb->coordinates);
                this->tiles.push_back(sb);
            }


            xlvl += 64;
        }
        yLvl+= 64;
        
    }

   
    //std::cout << "playerBottom " << playerOne.player.getPosition().y + playerOne.player.getGlobalBounds().height << std::endl;
    
    playerOne.groundYvalSetter(value);
    initWindow();
    this->rect.setSize(Vector2f(playerOne.player.getGlobalBounds().width, playerOne.player.getGlobalBounds().height));
    this->rect.setFillColor(Color(255, 0, 0));
    this->rect.setPosition(Vector2f(100.f, 200.f));
    this->rect.setOrigin(rect.getSize().x / 2.0f, rect.getSize().y / 2.0f);
    view.setSize(1200, 1200);
    

    sf::Vector2i topLeftWindow(0, 0); // Top-left corner of the window in window coordinates
    sf::Vector2f topLeftWorld = window->mapPixelToCoords(topLeftWindow);
    this->background.setTopLeftCoordinates(topLeftWorld);
    this->testEnemy.movementRange = Vector2f(800, 1000);
    this->testEnemy.player.setPosition(Vector2f(800, playerOne.player.getPosition().y+60));
}


void Game::initWindow(){ 
    window = new RenderWindow(VideoMode(width, height), title);
    window->setFramerateLimit(fps);
    running = true;
    
}

Game::~Game(){
    delete window;
    for(Tile *sb : this->tiles){
        delete sb;
    }
    delete this->testTile;
}


void Game::pollEvents(){
    while (window->pollEvent(ev)){
        if(ev.type == Event::Closed){
            window->close();
            running = false;
        }
    }
}




void Game::drawGround(){
    
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();
    int startIdx = static_cast<int>((center.x - size.x / 2) / 64); 
    int endIdx = static_cast<int>((center.x + size.x / 2) / 64);
    startIdx = std::max(startIdx, 0);
    endIdx = std::min(endIdx, static_cast<int>(this->tiles.size()) - 1);
        for(int i = startIdx; i <= endIdx; i++){
        window->draw(this->tiles[i]->block);
    } 
}


void Game::render(){
    window->clear();

    // Render the parallax background.
    background.render(*window);

    window->draw(playerOne.player);
    window->draw(testTile->block);
    //window->draw(this->rect);
    for(bullet *b:playerOne.bullets){
        window->draw(b->sprite);
    }
    drawGround();
    window->draw(this->testEnemy.player);
    window->display();
    //window->draw(testTile->block);
}

void Game::update(){
    
    // We check whether the player has moved since the last frame.
    // You will need to implement the Player::hasMoved() function.
    bool playerHasMoved = playerOne.update(*window);
    
    // Update the parallax background.
    background.update(playerHasMoved, view);
    playerOne.onGround = false;
    for(Tile *tile:this->tiles){
        if(playerOne.isOnTopOfBlock(tile->block)){
            playerOne.onGround = true;
            playerOne.floatingBlockInteract = false;
            break;
        }
    }
    playerOne.onFloatingBlock = false;
    if(playerOne.isOnTopOfBlock(testTile->block)){
        playerOne.onGround = true;
        playerOne.onFloatingBlock = true;
        playerOne.xVel = testTile->movementSpeed;
        playerOne.floatingBlockInteract = true;
    }

    
    //std::cout << this->testEnemy.player.getPosition().y << endl;
    //std::cout << playerOne.player.getPosition().y << endl;
    playerOne.update(*window);
    testTile->update(&playerOne.player, playerOne.onFloatingBlock);
    sf::Vector2f playerPos = playerOne.player.getPosition();
    float viewY = std::min(playerPos.y, initialBlockY - window->getSize().y / 2 + playerOne.player.getGlobalBounds().height);
    view.setCenter(playerPos.x, viewY);
    this->testEnemy.update();
    this->rect.setSize(Vector2f(playerOne.player.getGlobalBounds().width, playerOne.player.getGlobalBounds().height));
    this->rect.setPosition(Vector2f(playerOne.player.getPosition().x, 328.f)); //playerOne.player.getPosition().y
    window->setView(view);
    pollEvents();

}
