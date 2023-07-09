#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "stoneBlock.h"
#include "Tile.h"
#include "Parralax.h"
#include "floatingTile.h"
#include <vector>
#include "Enemy.h"
using namespace sf;
using namespace std;
class Game{
    private:
        Parralax background;
        int width, height, fps;
        RenderWindow *window;
        Event ev;
        const char* title;
        Player playerOne;
        stoneBlock *testBlock;
        vector<Tile*> tiles;
        View view;
        void initWindow();
        void pollEvents();
        RectangleShape rect;
        float initialBlockY;
        vector<floatingTile*> floatingTiles;
        
        Texture testTexture;
        bool checkPlayerOnGround();
        Enemy testEnemy;
        int gameLevel;
        char levelString[100];
        vector<Vector2f> floatingTilePos;
        Clock frameTimer;
        

    public:
        Game();
        ~Game();
        void update();
        void render();
        void drawGround();
        

        bool running = false;


};