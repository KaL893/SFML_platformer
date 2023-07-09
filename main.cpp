#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
using namespace sf;


int main(){
    Game game;
    std::cout << "SFML version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;
    while (game.running){
        game.update();
        game.render();
    }
    return 0;
}