#include "Load.hpp"

Load::Load( const int _amount, const int _bonus_time, const string _name, City *_from, City *_to) :
    amount(_amount), bonus_time(_bonus_time), name(_name), from(_from), to(_to)
{
    ID = Load::NextID();
    full_amount = amount;
}

Load::~Load() {}

bool Load::IsReady()
{
    if(amount > 0) return false;
    else return true;
}

void Load::GetCommands( priority_queue<string, vector<string>, CompareCommands> &all_commands)
{
    for(size_t i = 0; i < routes.size(); i++)
    {
        for(size_t j = 0; j < routes[i].GetCommands().size(); j++)
        {
            all_commands.push(routes[i].GetCommands()[j]);
        }
        routes[i].ClearCommands();
    }
}

int Load::GetFreeRouteNumber()
{
    int ret = 0;
    for(size_t i = 0; i < routes.size(); i++)
    {
        if(!routes[i].IsFull()) ret++;
    }
    return ret;
}

void Load::AddLoad(int &p)
{
    int index;
    for(size_t i = 0; i < routes.size(); i++)
    {
        if(!routes[i].IsFull())
        {
            index = i;
        }
    }
    amount = routes[index].AddLoad(amount, name, bonus_time, p);
}

void Load::FindRoute(ofstream &o, int p)
{
    Route route(from);
    o << "\nID: " << ID << " Mit: " << name << " Honnan: " << from->GetName() << " Hova: " << to->GetName();
    FindRouteIn(route, p);
    o << "\nA lehetseges utvonalak szama: " << routes.size() << endl;
}

void Load::FindRouteOutBonus()
{
    Route route(from);
    FindRouteOutBonusIn(route);
}

void Load::FindRouteIn(Route &r, int p)
{
    for(size_t i = 0; i < r.GetEndCity()->GetFromShip().size(); i++)
    {
        if( !r.Find(r.GetEndCity()->GetFromShip()[i]->GetEndCity()) ) /// r.Find don't find  = true
        {
            int k = 0;
            while(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time && k < p*2) /// addig futunk, ameddig a bonus idõn belül leszünk
            {
                if(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay()) /// ha a fordulo indulasakor ott van
                {
                    r.AddTurn(k,r.GetEndCity()->GetFromShip()[i]);
                    if(!r.IsFull()) /// az utvonal nincs tele, ha egyetlen egy fordulója sincsen tele
                    {
                        if(r.GetEndCity() == to) routes.push_back(r); /// if Rout EndCity = AimCity
                        else FindRouteIn(r,p); /// else az adott városból megyünk tovább
                    }
                    r.DeleteTurn();
                }
                k=k+2; /// csak az odafordulókat vizsgalja
            }
        }
    }

    for(size_t i = 0; i < r.GetEndCity()->GetToShip().size(); i++)  /// visszafelé irányuló utakra is vizsgálja meg (ptlan fordulókra)
    {
        if( !r.Find(r.GetEndCity()->GetToShip()[i]->GetStartCity()) )
        {
            int k = 1;
            while(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time && k < p*2+1)
            {
                if(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay())
                {
                    r.AddTurn(k,r.GetEndCity()->GetToShip()[i]);
                    if(!r.IsFull()) /// az utvonal nincs tele, ha egyetlen egy fordulója sincsen tele
                    {
                        if(r.GetEndCity() == to) routes.push_back(r); /// if Rout EndCity = AimCity
                        else FindRouteIn(r,p); /// else az adott városból megyünk tovább
                    }
                    r.DeleteTurn();
                }
                k=k+2;
            }
        }
    }
}

void Load::FindRouteOutBonusIn( Route &r )
{
    for(size_t i = 0; i < r.GetEndCity()->GetFromShip().size(); i++)
    {
        if( !r.Find(r.GetEndCity()->GetFromShip()[i]->GetEndCity()) )
        {
            int k = 0;
            while(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->IsFull() || r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetStartDay() < r.GetEndDay()) k+=2;
            r.AddTurn(k,r.GetEndCity()->GetFromShip()[i]);
            if(r.GetEndCity() == to) routes.push_back(r);
            else FindRouteOutBonusIn(r);
            r.DeleteTurn();

        }
        if(GetFreeRouteNumber() > 0) return;
    }

    for(size_t i = 0; i < r.GetEndCity()->GetToShip().size(); i++)
    {
        if( !r.Find(r.GetEndCity()->GetToShip()[i]->GetStartCity()) )
        {
            int k = 1;
            while(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->IsFull() || r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetStartDay() < r.GetEndDay()) k+=2;
            r.AddTurn(k,r.GetEndCity()->GetToShip()[i]);
            if(r.GetEndCity() == to) routes.push_back(r);
            else FindRouteOutBonusIn(r);
            r.DeleteTurn();
        }
        if(GetFreeRouteNumber() > 0) return;
    }
}
