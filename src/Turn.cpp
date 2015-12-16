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

int Turn::GetAllPriority() const
{
    int sum = 0;
    for(unsigned int i = 0; i < loads.size(); i++)
    {
        sum += loads[i].first;
    }
    return sum;
}

void Turn::AddLoad(Load *l)
{
    for(unsigned int i = 0; i < loads.size(); i++)
    {
        if(loads[i].second == l)
        {
            loads[i].first++;
            return;
        }
    }
    loads.push_back(pair< int,Load* >(0,l));
}
