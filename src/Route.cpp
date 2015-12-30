#include "Route.hpp"

Route::Route(City * _from) : Turn(_from,_from,0,0,80)
{
    //ctor
}

Route::~Route()
{
    //dtor
}

bool Route::IsFull()
{
    for(size_t i = 0; i < turns.size(); i++)
    {
        if(turns[i]->IsFull()) return true;
    }
    return false;
}

int Route::AddLoad( int amount)
{
    int free_cap;
    if(amount > GetFreeCap())
        free_cap = GetFreeCap();
    else
        free_cap = amount;
    for(size_t i = 0; i < turns.size(); i++)
    {
        turns[i]->AddLoad(free_cap);
    }
    return free_cap;
}

int Route::GetFreeCap()
{
    int min_cap = 80;
    for(size_t i = 0; i < turns.size(); i++)
    {
        if(turns[i]->GetFreeCap() < min_cap) min_cap = turns[i]->GetFreeCap();
    }
    return min_cap;
}

void Route::AddTurn(int turn_number, Ship* ship)
{
    turns.push_back(ship->GetTurn(turn_number));

    if(capacity > turns[turns.size()-1]->GetCap()) capacity = turns[turns.size()-1]->GetCap();

    endday = turns[turns.size()-1]->GetEndDay();
    to = turns[turns.size()-1]->GetEndCity();
}
void Route::DeleteTurn()
{
    turns.pop_back();

    if(turns.size() == 0)
    {
        endday = startday;
        to = from;
        capacity = 80;
    }
    else
    {
        int cap = 80;
        for(size_t i = 0; i < turns.size(); i++)
        {
            if( cap > turns[i]->GetCap()) cap = turns[i]->GetCap();
        }
        capacity = cap;
        endday = turns[turns.size()-1]->GetEndDay();
        to = turns[turns.size()-1]->GetEndCity();
    }
}

bool Route::Find(City* c)
{
    cout << c->GetName() << ", " << from->GetName() << " ";

    for( size_t i = 0; i < turns.size(); i++)
    {
        cout << turns[i]->GetEndCity()->GetName() << " ";

        if( turns[i]->GetEndCity() == c || turns[i]->GetStartCity() == c )
        {
            cout << endl;
            return true;
        }
    }
    cout << endl;
    return false;
}

