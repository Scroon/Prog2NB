#include "Turn.hpp"

Turn::Turn(City *_from, City *_to, const int _startday, const int _endday) : from(_from), to(_to), startday(_startday), endday(_endday)
{
    //ctor
}

Turn::~Turn()
{
    //dtor
}

int Turn::GetTravellTime() const
{
    return endday-startday;
}

int Turn::GetPriority() const
{
    return priority;
}
