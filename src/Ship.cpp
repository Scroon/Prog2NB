#include "Ship.hpp"

Ship::Ship()
{
    //ctor
}

Ship::~Ship()
{
    //dtor
}

Turn* Ship::GetTurn( const int index)
{
    return turns[index];
}
