// entityStates.h

#ifndef ENTITY_STATES_H
#define ENTITY_STATES_H

#include <iostream>

enum class movementState {Idle=0, IdleLeft, Right, Left, Jumping, Falling, Shooting, Hurt, Throwing};

inline std::ostream& operator<<(std::ostream& os, const movementState& state)
{
    switch(state)
    {
        case movementState::Idle: os << "Idle"; break;
        case movementState::Jumping: os << "Jumping"; break;
        case movementState::Right: os << "Right"; break;
        case movementState::Left: os << "Left"; break;
        case movementState::Hurt: os << "Hurt";break;
        // Add additional cases if you have more movement states
    }

    return os;
}
#endif // ENTITY_STATES_H
