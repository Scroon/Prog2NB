#include "Route.hpp"

Route::Route(City * _from) : from(_from), to(_from), startday(0), endday(0)
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

int Route::AddLoad( int amount, string name, int bonus )
{
    int cap;

    if(amount > GetFreeCap()) cap = GetFreeCap();
    else cap = amount;

    for(size_t i = 0; i < turns.size(); i++)
    {
        turns[i]->AddLoad(cap);
        string str = convertToString(turns[i]->GetStartDay()) + " " + turns[i]->GetShip()->GetName() + " " + name + " " + convertToString((bonus-turns[i]->GetEndDay())) + " " + convertToString(cap);
        commands.push_back(str);
    }

    return amount-cap;
}

int Route::GetFreeCap()
{
    int cap = 80;
    for(size_t i = 0; i < turns.size(); i++)
    {
        if(turns[i]->GetFreeCap() < cap) cap = turns[i]->GetFreeCap();
    }
    return cap;
}

int Route::GetCap()
{
    int cap = 80;
    for(size_t i = 0; i < turns.size(); i++)
    {
        if(turns[i]->GetCap() < cap) cap = turns[i]->GetCap();
    }
    return cap;
}

void Route::AddTurn(int turn_number, Ship* ship)
{
    turns.push_back(ship->GetTurn(turn_number));

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
    }
    else
    {
        endday = turns[turns.size()-1]->GetEndDay();
        to = turns[turns.size()-1]->GetEndCity();
    }
}

bool Route::Find(City* c)
{
    //cout << c->GetName() << ", " << from->GetName() << " ";

    for( size_t i = 0; i < turns.size(); i++)
    {
        //cout << turns[i]->GetEndCity()->GetName() << " ";

        if( turns[i]->GetEndCity() == c || turns[i]->GetStartCity() == c )
        {
            //cout << endl;
            return true;
        }
    }
    //cout << endl;
    return false;
}

