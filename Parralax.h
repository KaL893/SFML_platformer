#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class Parralax{

    public:
        Parralax(float playerMovementSpeed);
        ~Parralax();
        void update(bool playerMoved, View View);
        void render(RenderWindow &target);
        
        Texture layer1;
        Texture layer2;
        Texture layer3;
        Texture layer4;
        Texture layer5;
        Texture layer6;
        bool activeX;

        Sprite sprite1;
        Sprite sprite2;
        Sprite sprite3;
        Sprite sprite4;
        Sprite sprite5;
        Sprite sprite6;
        Sprite sprite1b;
        Sprite sprite2b;
        Sprite sprite3b;
        Sprite sprite4b;
        Sprite sprite5b;
        Sprite sprite6b;
    private:
        Vector2f viewTopLeft;
        float playerMovementSpeed;
        float layerOneMovementSpeed;
        float layerTwoMovementSpeed;
        float layerThreeMovementSpeed;
        float layerFourMovementSpeed;




};

