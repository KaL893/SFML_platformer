
#include <iostream>
#include <SFML/Graphics.hpp>
#include "gameBlock.h"

#ifndef healthPickup_H
#define healthPickup_H
class healthPickup : public gameBlock{

    public:
        healthPickup();
        void update();
        float tally;
        int direction;
        float movementIncrements;

    
    private:

};

#endif