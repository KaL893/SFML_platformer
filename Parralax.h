#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class Parralax{

    public:
        Parralax(float playerMovementSpeed);
        ~Parralax();
        void update(bool playerMoved, View View);
        void render(RenderWindow &target);
        void setTopLeftCoordinates(Vector2f topLeft);
        Texture layerFourTexture; Sprite layerFour;
        Texture layerThreeTexture; Sprite layerThree;
        Texture layerTwoTexture; Sprite layerTwo;
        Texture layerOneTexture; Sprite layerOne;
        sf::Sprite layerOneB; // Duplicate layer
        sf::Sprite layerTwoB;
        sf::Sprite layerThreeB;
        sf::Sprite layerFourB;
        

    private:
        Vector2f viewTopLeft;
        float playerMovementSpeed;
        float layerOneMovementSpeed;
        float layerTwoMovementSpeed;
        float layerThreeMovementSpeed;
        float layerFourMovementSpeed;




};

