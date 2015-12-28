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
    if(turns.find(index) == turns.end())
    {
        int start_day = startday+(index%2)*(days_there)+(index/2)*(days_back+days_there);
        int end_day = startday+((1+index)%2)*(days_there)+((1+index)/2)*(days_back+days_there);

        turns[index] = new Turn(from,to,start_day,end_day);
    }

    return turns.find(index)->second;
}

void Ship::AddToCity()
{
    to->AddToShip(name);
    from->AddFromShip(name);
}
