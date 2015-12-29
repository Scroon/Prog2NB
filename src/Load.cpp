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

    BuildRoute( route, route->GetEndCity()->GetFromShipsName(), route->GetEndCity()->GetToShipsName(), ships);

    delete route;

    cout << "A lehetseges utvonalak szama: " << routes.size() << endl;
}

void Load::BuildRoute(Route * r, vector<string> ships_from, vector<string> ships_to,  map< string, Ship* > ships )
{
    for( size_t i = 0; i < ships_from.size(); i++)
    {
        cout << endl;
        cout << "Honnan: " << from->GetName() << " Hova: " << to->GetName() << endl;
        cout << endl;

        cout << ships_from.size() << " " << ships_from[i] << " ";
        cout << ships.find(ships_from[i])->second->GetStartCity()->GetName() << " ";
        cout << ships.find(ships_from[i])->second->GetEndCity()->GetName() << endl;

        if( !r->TravellPass(ships.find(ships_from[i])->second->GetEndCity()))
        {
            int k = 0;

            cout << ships.find(ships_from[i])->second->GetTurn(k)->GetEndDay() << " ";
            cout << bonus_time << " " << k << endl;

            while(ships.find(ships_from[i])->second->GetTurn(k)->GetEndDay() <= bonus_time)
            {
                cout << ships.find(ships_from[i])->second->GetTurn(k)->GetStartDay() << " ";
                cout << r->GetEndDay() << endl;

                if(ships.find(ships_from[i])->second->GetTurn(k)->GetStartDay() >= r->GetEndDay())
                {
                    Route * route;
                    route = r->Copy();
                    route->AddTurn(k,ships.find(ships_from[i])->second);

                    if(route->GetEndCity() == to){
                        cout << "Utvonal hozzaadva" << endl;
                        routes.push_back(r);
                    }
                    else BuildRoute(route,route->GetEndCity()->GetFromShipsName(),route->GetEndCity()->GetToShipsName(),ships);

                    if (route->IsWrong())
                    {
                        cout << "Teves utvonal, torolve" << endl;
                        delete route;
                    }
                }
                k=k+2;

                cout << ships.find(ships_from[i])->second->GetTurn(k)->GetEndDay() << " ";
                cout << bonus_time << " " << k << endl;

                if (k == 20) break;

                //string s;
                //cin >> s;
            }
        }
        else r->SetWrong();
        cout << endl;
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
