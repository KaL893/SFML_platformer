#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation{

public:
    Animation();
    ~Animation();
    void update(int row, float deltaTime, bool faceRight);
    IntRect uvRect;

private:
    Vector2u imageCount;
    Vector2u currImage;
    void setAttributes(Texture *Texture, Vector2u imageCount, float switchTime);
    
    float totalTime;
    float switchTime;


};