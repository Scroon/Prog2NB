#include "Route.hpp"

Route::Route(City * _from) : from(_from), to(_from), startday(0), endday(0) {}

Route::~Route() {}

bool Route::IsFull()
{
    for(size_t i = 0; i < turns.size(); i++)
    {
        if(turns[i]->IsFull()) return true;
    }
    return false;
}

int Route::AddLoad( int amount, string name, int bonus, int &p )
{
    int cap;
    int rem_bonus;

    if(amount > GetFreeCap()) cap = GetFreeCap();
    else cap = amount;

    if(bonus-turns[turns.size()-1]->GetStartDay() < 0)
    {
        rem_bonus = 0;
        p += cap*10;
    }
    else
    {
        rem_bonus = bonus-turns[turns.size()-1]->GetStartDay();
        p += cap*30;
    }

    for(size_t i = 0; i < turns.size(); i++)
    {
        turns[i]->AddLoad(cap);
        string str = convertToString(turns[i]->GetStartDay()) + " " + turns[i]->GetShip()->GetName() + " " + name + " " + convertToString(rem_bonus) + " " + convertToString(cap);
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
    for( size_t i = 0; i < turns.size(); i++)
    {
        if( turns[i]->GetEndCity() == c || turns[i]->GetStartCity() == c ) return true;
    }
    if(from == c) return true;
    return false;
}

