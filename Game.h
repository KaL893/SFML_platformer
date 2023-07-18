#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "stoneBlock.h"
#include "Tile.h"
#include "Parralax.h"
#include "floatingTile.h"
#include <vector>
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "memory"
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
        vector<shared_ptr<Tile>> tiles;
        vector<Sprite*> tileSprites;
        View view;
        void initWindow();
        void pollEvents();
        RectangleShape rect;
        float initialBlockY;
        vector<floatingTile*> floatingTiles;
        View backGroundView;
        Texture testTexture;
        bool checkPlayerOnGround();
        Enemy testEnemy;
        int gameLevel;
        char levelString[100];
        vector<Vector2f> floatingTilePos;
        vector<shared_ptr<Enemy>> enemies;
        Clock frameTimer;
        SoundBuffer OST;
        Sound gameSound;
        

    public:
        Game();
        ~Game();
        void update();
        void render();
        void drawGround();
        

        bool running = false;


};