#include "Route.hpp"

Route::Route(City * _from, City * _to, const int _startday, const int _endday) : Turn(_from,_to,_startday,_endday)
{
    //ctor
}

Route::~Route()
{
    //dtor
}

int Route::GetRoutePriority()
{
    int max_priority = 0;
    for( size_t i = 0; i < turns.size(); i++ )
    {
        if(turns[i].second->GetTurn(turns[i].first)->GetAllPriority() > max_priority) {
            max_priority = turns[i].second->GetTurn(turns[i].first)->GetAllPriority();
        }
    }
    return max_priority;
}
