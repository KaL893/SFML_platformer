#include <iostream>

#include "player.h"
#include "stoneBlock.h"
#include "Tile.h"
#include "Parralax.h"
#include "Spikes.h"
#include "floatingTile.h"
#include <vector>
#include <SFML/Audio.hpp>
#include "Enemy.h"
#include "memory"
#include "healthPickup.h"
#include "Menu.h"
using namespace sf;
using namespace std;


enum gameState {Start, Playing, End};


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
        vector<shared_ptr<Spikes>> spikeTiles;
        vector<Sprite*> spikeSprites;
        vector<shared_ptr<healthPickup>> healthPickups;
        vector<Sprite*> healthPickupSprites;
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
        Menu *menu;
        gameState gameSt;
        bool gameStarted;

        
        
        

    public:
        Game();
        ~Game();
        void update();
        void render();
        void drawGround();
        

        bool running = false;


};