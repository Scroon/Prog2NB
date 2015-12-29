#include "Route.hpp"

Route::Route(City * _from) : Turn(_from,_from,0,0), wrong(false)
{
    //ctor
}

Route::Route(City * _from, City * _to, int _startday, int _endday, vector< pair< int, Ship* > > _turns) : Turn(_from,_from,_startday,_endday), turns(_turns), wrong(false)
{
    //ctor
}

Route::~Route()
{
    //dtor
}

int Route::GetPriority() const
{
    if( turns.size() == 0 ) return 0;

    int max_priority = 0;

    for( size_t i = 0; i < turns.size(); i++ )
    {
        if(turns[i].second->GetTurn(turns[i].first)->GetPriority() > max_priority) {
            max_priority = turns[i].second->GetTurn(turns[i].first)->GetPriority();
        }
    }
    return max_priority;
}

void Route::AddTurn(int turn_number, Ship* ship)
{
    turns.push_back(pair<int,Ship*>(turn_number,ship));

    startday = turns[0].second->GetTurn(turns[0].first)->GetStartDay();
    endday = turns[turns.size()-1].second->GetTurn(turns[turns.size()-1].first)->GetEndDay();

    to = turns[turns.size()-1].second->GetTurn(turns[turns.size()-1].first)->GetEndCity();
}

bool Route::TravellPass(City* c)
{
    cout << from->GetName() << " ";

    for( size_t i = 0; i < turns.size(); i++)
    {
        cout << turns[i].second->GetEndCity()->GetName() << " ";

        if( turns[i].second->GetEndCity() == c || turns[i].second->GetStartCity() == c )
        {
            cout << endl;
            return true;
        }
    }
    if(from == c) {
        cout << endl;
        return true;
    }

    cout << endl;
    return false;
}

Route* Route::Copy()
{
    Route* route = new Route(from,to,startday,endday,turns);
    return route;
}

