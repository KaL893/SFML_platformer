#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "bullet.h"
#include "string"
#include "Grenade.h"
#include <fstream>
#include <string>
#include <vector>
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
    this->initialBlockY = 512;
    backGroundView.setSize(262, 160);
    backGroundView.setCenter(150, 81);
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
    int enemyCount;
    vector<Vector2f> enemyPositions;
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

    std::string soldierMovementLines;
    std::ifstream soldierMovementRanges("soldierMovementRanges.txt");
    while(std::getline(soldierMovementRanges, soldierMovementLines)){
        Vector2f positions = parseStringToVector2f(soldierMovementLines);
        enemyPositions.push_back(positions);
    }
    this->OST.loadFromFile("OST.ogg");
    this->gameSound.setLoop(true);
    this->gameSound.setBuffer(this->OST);
    //this->gameSound.play();



    
    int floatingTileCount = 0;
    while(std::getline(file, line)){
        xlvl = 0;
        for(char& c : line) {
            // Now 'c' is the character in the line.
           
            if(c == '='){
                Tile *sb_raw = new Tile();
                sb_raw->coordinates = Vector2f(xlvl, yLvl);
                sb_raw->block.setPosition(sb_raw->coordinates);
                std::shared_ptr<Tile> sb(sb_raw);
                this->tiles.push_back(sb);
                this->tileSprites.push_back(&(sb->block));
                
            }else if (c == '-')
            {   
                cout << "\nupperBound: " << this->floatingTilePos[floatingTileCount].y*64 << endl;
                cout << "\nlowerBound: " << this->floatingTilePos[floatingTileCount].x*64 << endl;
                floatingTile *iteratorTile = new floatingTile(this->floatingTilePos[floatingTileCount].x*64, this->floatingTilePos[floatingTileCount].y*64, true, yLvl, this->testTexture, 2);
                iteratorTile->num = floatingTileCount;
                iteratorTile->block.setPosition(xlvl, yLvl);
                this->floatingTiles.push_back(iteratorTile);
                
                floatingTileCount++;
            }else if(c == 'P'){
                playerOne.player.setPosition(xlvl, yLvl);
            }else if(c == 'E'){
                Enemy *newEnemyRaw = new Enemy();
                newEnemyRaw->player.setPosition(xlvl, yLvl);
                newEnemyRaw->healthStatus = healthBar(10.f, 70.f, Vector2f(xlvl-30, yLvl-100));
                newEnemyRaw->movementRange = enemyPositions[enemyCount++];
                shared_ptr<Enemy> newEnemy(newEnemyRaw);
                this->enemies.push_back(newEnemy); 
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
    
    // this->testEnemy.player.setPosition(Vector2f(800, playerOne.player.getPosition().y+60));
    this->frameTimer.restart();
}


void Game::initWindow(){ 
    window = new RenderWindow(VideoMode(width, height), title);
    window->setFramerateLimit(fps);
    running = true;
    
}

Game::~Game(){
    delete window;
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


void Game::render() {
    window->clear();

    // Set the background view and draw the parallax background
    window->setView(backGroundView);
    background.render(*window);

    //Set the game view before drawing the game objects
    window->setView(view);

    //Draw the player
    window->draw(playerOne.player);
    if(playerOne.damageTimer.getElapsedTime().asSeconds() <= 0.6f){
        playerOne.healthStatus.draw(window);
    }
    // Draw the other elements
    for(bullet *b : playerOne.bullets) {
        window->draw(b->sprite);
    }

    for(Grenade *g : this->playerOne.grenades) {
        window->draw(g->sprite);
    }

    for(auto& t : this->tiles) {
        window->draw(t->block);
    }


    for(floatingTile *tile : this->floatingTiles) {
        window->draw(tile->block);
    }

    // Render the enemy
    for(auto& ptr: this->enemies){
        window->draw(ptr->player);
        if(ptr->damageTimer.getElapsedTime().asSeconds() <= 0.6f){
            ptr->healthStatus.draw(window);
        }
        for(bullet *b : ptr->bullets){
            window->draw(b->sprite);
        }
    }

    //Display everything
    window->display();
    this->frameTimer.restart();
}


void Game::update(){
    
    // We check whether the player has moved since the last frame.
    // You will need to implement the Player::hasMoved() function.
     // This will be your vector of Sprites
    
    
    float dt = this->frameTimer.getElapsedTime().asSeconds();
    bool playerHasMoved = playerOne.update(*window, dt,this->tileSprites, view);

    

    //cout << this->playerOne.player.getPosition().x << std::endl;
    // Update the parallax background.
    for(auto& enemy:this->enemies){
        playerOne.checkForBulletCollision(enemy->bullets);
    }
    
    //cout << playerOne.getState() << ": 1" << endl;
    playerOne.onGround = false;
    for(auto& tile : this->tiles){
        if(playerOne.isOnTopOfBlock(tile->block)){
            playerOne.onGround = true;
            playerOne.floatingBlockInteract = false;
            break;
        }
    }
    




    
    playerOne.onFloatingBlock = false;
    background.update(playerHasMoved, backGroundView);
    

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

    playerOne.update(*window, dt,this->tileSprites, view);
    
    
    //std::cout << this->testEnemy.player.getPosition().y << endl;
    //std::cout << playerOne.player.getPosition().y << endl
    //cout << playerOne.getState() << ": 2" << endl;
    for(floatingTile *tile : this->floatingTiles){
        tile->update(&playerOne.player, &playerOne.healthStatus.bar, &playerOne.healthStatus.outline);
    }
    sf::Vector2f playerPos = playerOne.player.getPosition();
    float viewY = std::min(playerPos.y, initialBlockY - window->getSize().y / 2 + playerOne.player.getGlobalBounds().height);
    view.setCenter(playerPos.x, 512.f-600);
    for(auto& enemy : this->enemies){
    enemy->update(&playerOne.player, playerOne.bullets, playerOne.grenadeSprites, view);
    }

    this->enemies.erase(std::remove_if(this->enemies.begin(), this->enemies.end(), [](const std::shared_ptr<Enemy>& enemy){
        return !enemy->active;
    }), this->enemies.end());

    this->rect.setSize(Vector2f(playerOne.player.getGlobalBounds().width, playerOne.player.getGlobalBounds().height));
    this->rect.setPosition(Vector2f(playerOne.player.getPosition().x, 328.f)); //playerOne.player.getPosition().y
    
    pollEvents();
   

}
