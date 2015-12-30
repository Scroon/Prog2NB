#include "Turn.hpp"

Turn::Turn(Ship * _ship, City *_from, City *_to, const int _startday, const int _endday, const int _capacity) : ship(_ship), from(_from), to(_to), startday(_startday), endday(_endday), capacity(_capacity), used_cap(0)
{
    //ctor
}

Turn::~Turn()
{
    //dtor
}

bool Turn::IsFull()
{
    if(used_cap < capacity) return false;
    else return true;
}

void Turn::AddLoad(int amount)
{
    if(amount <= GetFreeCap()) used_cap += amount;
    else used_cap = capacity;
}
