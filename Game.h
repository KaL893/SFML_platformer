#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
using namespace sf;
class Game{
    private:
        int width, height, fps;
        RenderWindow *window;
        Event ev;
        const char* title;
        Player playerOne;
        void initWindow();
        void pollEvents();

    public:
        Game();
        ~Game();
        void update();
        void render();
        

        bool running = false;


};