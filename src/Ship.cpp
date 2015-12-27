#include "Ship.hpp"

Ship::Ship(const string _name, City* &_from, City* &_to, const int _startday, const int _days_there, const int _days_back, const int _capacity) :
    name(_name), from(_from), to(_to), startday(_startday), days_there(_days_there), days_back(_days_back), capacity(_capacity)
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

void Ship::AddToCity()
{
    to->AddToShip(name);
    from->AddFromShip(name);
}
