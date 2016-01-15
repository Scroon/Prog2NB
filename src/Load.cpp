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
    int index = -1;


    for(size_t i = 0; i < routes.size(); i++)
    {
        if(!routes[i].IsFull())
        {
            if(index == -1 || routes[i].GetEndDay() < routes[index].GetEndDay()) index = i;
        }
    }

    if(index != -1) amount = routes[index].AddLoad(amount, name, bonus_time, p);
}

void Load::FindRoute(ofstream &o, int precision, bool out_bonus)
{
    int k = 1;
    while(out_bonus && GetFreeRouteNumber() == 0)
    {
        k++;
        Route route(from);
        FindRouteIn(route, precision, k, out_bonus);
    }

    o << "\nID: " << ID << " Mit: " << name << " Honnan: " << from->GetName() << " Hova: " << to->GetName();

    if(!out_bonus)
    {
        Route route(from);
        FindRouteIn(route, precision, k, out_bonus);
        o << "A lehetseges utvonalak szama: " << routes.size() << endl;
    }
}

bool Load::GetPrecision(bool is_off, int precision, int turn_number, int bonus_multiply)
{
        if(is_off)
        {
            if(turn_number < (precision+bonus_multiply)*2) return true;
            else return false;
        }
        else
        {
            if(turn_number < precision*2) return true;
            else return false;
        }
}

void Load::FindRouteIn(Route &r, int precision, int bonus_multiply, bool out_bonus)
{
    for(size_t i = 0; i < r.GetEndCity()->GetFromShip().size(); i++)
    {
        if( !r.Find(r.GetEndCity()->GetFromShip()[i]->GetEndCity()) ) /// r.Find don't find  = true
        {
            int k = 0;
            while(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time*bonus_multiply && GetPrecision(out_bonus,precision,k,bonus_multiply)) /// addig futunk, ameddig a bonus idõn belül leszünk
            {
                if(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay()) /// ha a fordulo indulasakor ott van
                {
                    r.AddTurn(k,r.GetEndCity()->GetFromShip()[i]);
                    if(!r.IsFull()) /// az utvonal nincs tele, ha egyetlen egy fordulója sincsen tele
                    {
                        if(r.GetEndCity() == to) routes.push_back(r); /// if Rout EndCity = AimCity
                        else FindRouteIn(r,precision,bonus_multiply,out_bonus); /// else az adott városból megyünk tovább
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
            while(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time*bonus_multiply && GetPrecision(out_bonus,precision,k,bonus_multiply))
            {
                if(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay())
                {
                    r.AddTurn(k,r.GetEndCity()->GetToShip()[i]);
                    if(!r.IsFull()) /// az utvonal nincs tele, ha egyetlen egy fordulója sincsen tele
                    {
                        if(r.GetEndCity() == to) routes.push_back(r); /// if Rout EndCity = AimCity
                        else FindRouteIn(r,precision,bonus_multiply,out_bonus); /// else az adott városból megyünk tovább
                    }
                    r.DeleteTurn();
                }
                k=k+2;
            }
        }
    }
}
