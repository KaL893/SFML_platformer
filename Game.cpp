#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "bullet.h"
#include "string"
#include <fstream>
#include <string>
using namespace std;



#include <string>
#include <sstream>
#include <SFML/System.hpp>

#include <SFML/System.hpp>

sf::Vector2f parseStringToVector2f(const std::string& str) {
    float x, y;

    if(sscanf(str.c_str(), "(%f, %f)", &x, &y) != 2) {
        throw std::runtime_error("Invalid format");
    }
    cout << "x: " << x << " y:" << y << endl;
    return sf::Vector2f(x, y);
}



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
    
    std::string line;
    std::ifstream file(this->levelString);       
    // for(int i = 0; )
    int yLvl = 0;
    int xlvl;
    std::string floatingTileLines;
    std::ifstream floatingTileFile("FloatingTilePositions.txt");
    while(std::getline(floatingTileFile, floatingTileLines)){
        Vector2f positions = parseStringToVector2f(floatingTileLines);
        this->floatingTilePos.push_back(positions);
    }


    
    int floatingTileCount = 0;
    while(std::getline(file, line)){
        xlvl = 0;
        for(char& c : line) {
            // Now 'c' is the character in the line.
           
            if(c == '='){
                Tile *sb = new Tile();
                sb->coordinates = Vector2f(xlvl, this->initialBlockY);
                sb->block.setPosition(sb->coordinates);
                this->tiles.push_back(sb);
            }else if (c == '-')
            {   
                cout << "\nupperBound: " << this->floatingTilePos[floatingTileCount].y*64 << endl;
                cout << "\nlowerBound: " << this->floatingTilePos[floatingTileCount].x*64 << endl;
                floatingTile *iteratorTile = new floatingTile(this->floatingTilePos[floatingTileCount].x*64, this->floatingTilePos[floatingTileCount].y*64, true, yLvl, this->testTexture, 2);
                iteratorTile->num = floatingTileCount;
                iteratorTile->block.setPosition(xlvl, yLvl);
                this->floatingTiles.push_back(iteratorTile);

                floatingTileCount++;
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
    for(floatingTile* sb: this->floatingTiles){
        delete sb;
    }
    
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
}


void Game::render(){
    window->clear();

    // Render the parallax background.
    background.render(*window);

    window->draw(playerOne.player);
   
    //window->draw(this->rect);
    for(bullet *b:playerOne.bullets){
        window->draw(b->sprite);
    }
    // drawGround();
    for(Tile *t :this->tiles){
        window->draw(t->block);
    }

    for(floatingTile *tile:this->floatingTiles){
        window->draw(tile->block);
    }

    window->draw(this->testEnemy.player);
    window->display();
    //window->draw(testTile->block);
}

void Game::update(){
    
    // We check whether the player has moved since the last frame.
    // You will need to implement the Player::hasMoved() function.
    bool playerHasMoved = playerOne.update(*window);
    //cout << this->playerOne.player.getPosition().x << std::endl;
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
    for(floatingTile *floatingBlock: this->floatingTiles){
        if(playerOne.isOnTopOfBlock(floatingBlock->block)){
            playerOne.onGround = true;
            playerOne.onFloatingBlock = true;
            playerOne.floatingBlockInteract = true;
            floatingBlock->playerOnTop = true;
        }else{
            floatingBlock->playerOnTop = false;
        }
    }

    
    //std::cout << this->testEnemy.player.getPosition().y << endl;
    //std::cout << playerOne.player.getPosition().y << endl;
    playerOne.update(*window);
    for(floatingTile *tile : this->floatingTiles){
        tile->update(&playerOne.player);
    }
    sf::Vector2f playerPos = playerOne.player.getPosition();
    float viewY = std::min(playerPos.y, initialBlockY - window->getSize().y / 2 + playerOne.player.getGlobalBounds().height);
    view.setCenter(playerPos.x, viewY);
    this->testEnemy.update();
    this->rect.setSize(Vector2f(playerOne.player.getGlobalBounds().width, playerOne.player.getGlobalBounds().height));
    this->rect.setPosition(Vector2f(playerOne.player.getPosition().x, 328.f)); //playerOne.player.getPosition().y
    window->setView(view);
    pollEvents();

}
