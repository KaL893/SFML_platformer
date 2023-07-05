#include "gameBlock.h"

using namespace sf;
class floatingTile : public gameBlock{

    public:
        floatingTile(float lowerBound, float upperBound, bool xMoving, float yVal, Texture blockTexture, float movementSpeed);
        bool xMoving;
        Vector2f movementRange;
        void update(Sprite *Player, bool playerOn);
        int vel;
        float movementSpeed;
    private:

};
