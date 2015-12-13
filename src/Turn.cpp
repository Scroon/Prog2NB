#include "Turn.hpp"

Turn::Turn()
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

int Turn::GetAllPrority() const
{
    int sum = 0;
    for(int i = 0 : loads.size())
    {
        sum += loads[i].first;
    }
    return sum;
}
