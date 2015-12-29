#include "Load.hpp"

Load::Load( const int _amount, const int _bonus_time, const string _name, City *_from, City *_to) : amount(_amount), bonus_time(_bonus_time), name(_name), from(_from), to(_to)
{
    ID = Load::NextID();
}

Load::~Load()
{

}

void Load::AddRoute(map<string, Ship*> ships )
{
    Route * route = new Route(from);

    cout << "Honnan: " << from->GetName() << " Hova: " << to->GetName() << endl;

    BuildRoute( *route, route->GetEndCity()->GetFromShipsName(), route->GetEndCity()->GetToShipsName(), ships);
}

void Load::BuildRoute(Route r, vector<string> ships_from, vector<string> ships_to,  map< string, Ship* > ships )
{
    for( size_t i = 0; i < ships_from.size(); i++) {

        cout << ships_from[i] << " ";
        cout << ships.find(ships_from[i])->second->GetEndCity()->GetName() << endl;

        if( !r.TravellPass(ships.find(ships_from[i])->second->GetEndCity()) )
        {
            int k = 0;
            while(ships.find(ships_from[i])->second->GetTurn(k)->GetEndDay() <= bonus_time)
            {
                if(ships.find(ships_from[i])->second->GetTurn(k)->GetStartDay() >= r.GetEndDay())
                {
                    r.AddTurn(k,ships.find(ships_from[i])->second);

                    if(r.GetEndCity() == to) routes.push_back(&r);
                    else BuildRoute(r,r.GetEndCity()->GetFromShipsName(),r.GetEndCity()->GetToShipsName(),ships);
                }
                cout << k << endl;
                k=k+2;
            }
        }
    }
/*
    for( size_t i = 0; i < ships_to.size(); i++) {
        cout << ships_from[i] << " 2" << endl;
        if( !r.TravellPass(ships.find(ships_to[i])->second->GetStartCity()) )
        {
            int k = 1;
            while(ships.find(ships_to[i])->second->GetTurn(k)->GetEndDay() <= bonus_time)
            {
                if(ships.find(ships_to[i])->second->GetTurn(k)->GetStartDay() >= r.GetEndDay())
                {
                    r.AddTurn(k,ships.find(ships_to[i])->second);

                    if(r.GetEndCity() == to) routes.push_back(&r);
                    else BuildRoute(r,r.GetEndCity()->GetFromShipsName(),r.GetEndCity()->GetToShipsName(),ships);
                }
                cout << k << endl;
                k=k+2;
            }
        }
    }*/
}
