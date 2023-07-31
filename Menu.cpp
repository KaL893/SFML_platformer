#include "Menu.h"
using namespace std;
Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf"))
    {
       cout << "FAILED TO LOAD" << endl;
       exit(1);
    }

    startButton.setFont(font);
    startButton.setCharacterSize(40);
    startButton.setFillColor(sf::Color::White);
    startButton.setString("Start Game");
    startButton.setPosition(sf::Vector2f(width / 2, height / 3));

    instructions.setFont(font);
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color::White);
    instructions.setString("WASD to move, Space bar to jump, aim with mouse, left to shoot bullets, and G to throw grenades");
    instructions.setPosition(sf::Vector2f(width / 4, height / 2));
    start = true;
    end.setFont(font);
    end.setCharacterSize(40);
    end.setFillColor(sf::Color::White);
    end.setString("WOHOOO you killed all the bad guys!!");
    end.setPosition(sf::Vector2f(width / 4, height / 2));

}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    if(start){
        window.draw(startButton);
        window.draw(instructions);
    }else{
        window.draw(end);
        
    }
    
}
