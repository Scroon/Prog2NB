#include "Load.hpp"

Load::Load( const int _amount, const int _bonus_time, const string _name, City *_from, City *_to) :
    amount(_amount), bonus_time(_bonus_time), name(_name), from(_from), to(_to)
{
    ID = Load::NextID();
}

Load::~Load() {}

bool Load::IsReady()
{
    if(amount > 0) return false;
    else return true;
}

void Load::GetCommands( priority_queue<string, vector<string>, greater<string> > &all_commands)
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

<<<<<<< HEAD
void Load::FindRoute()
{
=======
int Load::GetFreeRouteNumber()
{
    int ret = 0;
    for(size_t i = 0; i < routes.size(); i++)
    {
        if(!routes[i].IsFull()) ret++;
    }
    return ret;
}

void Load::AddLoad()
{
    int index;
    //size_t num = 0;

    for(size_t i = 0; i < routes.size(); i++)
    {
        if(!routes[i].IsFull() /*&& (num == 0 || num > routes[i].GetSize())*/)
        {
            index = i;
        }
    }
    amount = routes[index].AddLoad(amount, name, bonus_time);
}
>>>>>>> refs/remotes/origin/master

void Load::FindRoute()
{
    Route route(from);
    int t = 0;

    cout << endl;
    cout << "ID: " << ID << " Mit: " << name << " Honnan: " << from->GetName() << " Hova: " << to->GetName() << endl;
    cout << "...";

    FindRouteIn(route, t);

    cout << endl;
    cout << "A lehetseges utvonalak szama: " << routes.size() << endl;
}

<<<<<<< HEAD
void Load::_SetPossibleRoutes (Route route)
{
    poss_routes.push_back(route);
}


void Load::FindRouteIn(Route r, int &t)
{

=======
void Load::FindRouteIn(Route r, int &t)
{
>>>>>>> refs/remotes/origin/master
    t++;
    if(t == 10000)
    {
        t = 0;
        cout << ".";
    }

    for(size_t i = 0; i < r.GetEndCity()->GetFromShip().size(); i++)
    {
        if( !r.Find(r.GetEndCity()->GetFromShip()[i]->GetEndCity()) ) /// r.Find don't find  = true
        {
            int k = 0;
            while(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time) /// addig futunk, ameddig a bonus idõn belül leszünk
            {
                if(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay()) /// ha még célba tudom juttatni
                {
                    r.AddTurn(k,r.GetEndCity()->GetFromShip()[i]);
                    if(!r.IsFull()) /// ha egyetlen egy forduló sincsen tele
                    {
                        if(r.GetEndCity() == to) routes.push_back(r); /// if Rout EndCity = AimCity
                        else FindRouteIn(r,t); /// else az adott városból megyünk tovább
                    }
                    r.DeleteTurn();
                }
                k=k+2; /// csak az odafordulókat vizsglja
            }
        }
    }

    for(size_t i = 0; i < r.GetEndCity()->GetToShip().size(); i++) /// visszafelé irányuló utakra is vizsgálja meg (ptlan fordulókra)
    { /// azért, mert lehet hogy a 2. fordulóval már el fogja tudni vinni a szállítmányt a hajó
        cout << endl;
        cout << r.GetEndCity()->GetToShip().size() << " ";
        cout << i+1<< " ";
        cout << r.GetEndCity()->GetToShip()[i]->GetName() << " ";
        cout << r.GetEndCity()->GetToShip()[i]->GetStartCity()->GetName() << " ";
        cout << r.GetEndCity()->GetToShip()[i]->GetEndCity()->GetName() << endl;

        if( !r.Find(r.GetEndCity()->GetToShip()[i]->GetStartCity()) )
        {
            int k = 1;
//            cout << "Fordulo: " << k << ", fordulo erkezese: " << r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetEndDay() << ", bonuszido:  " << bonus_time << endl;
            while(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time )
            {
                cout << "Fordulo indulasa: " << r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetStartDay() << ", csomag erkezese: " << r.GetEndDay() << endl;
                if(r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay())
                {
                    r.AddTurn(k,r.GetEndCity()->GetToShip()[i]);
                    if(r.GetEndCity() == to)routes.push_back(r);
                    else _SetPossibleRoutes(r);
                    r.DeleteTurn();
                }
                k=k+2;
                cout << "\nFordulo: " << k << ", fordulo erkezese: " << r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetEndDay() << ", bonuszido:  " << bonus_time << endl;
            }
        }
    }
}
