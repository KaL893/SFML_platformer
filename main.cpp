#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
using namespace sf;


int main(){
    Game game;
    
    while (game.running){
        game.update();
        game.render();
    }
    return 0;
}