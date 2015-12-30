#include "Load.hpp"

Load::Load( const int _amount, const int _bonus_time, const string _name, City *_from, City *_to) : amount(_amount), bonus_time(_bonus_time), name(_name), from(_from), to(_to), ready(false)
{
    ID = Load::NextID();
}

Load::~Load()
{

}

bool Load::IsReady()
{
    if(ready) return ready;
    else
    {
        float sum = 0;
        for(size_t i = 0; i < routes.size(); i++)
        {
            sum += routes[i].GetFreeCap();
        }
        if( sum >= amount)
        {
            for(size_t i = 0; i < routes.size(); i++)
            {
                if(amount > 0) amount -= routes[i].AddLoad(amount);
            }
            ready = true;
            return ready;
        }
        else return ready;
    }
}

void Load::WriteLog(ofstream &o)
{
    o << ID << " " << routes.size() << ready << endl;
}

void Load::SetPossibleRoutes() {

    Route route(from);

    cout << endl;
    cout << "Honnan: " << from->GetName() << " Hova: " << to->GetName() << endl;
    cout << endl;

    _SetPossibleRoutes(route);

    cout << endl;
    cout << "A lehetseges utvonalak szama: " << routes.size() << endl;
    cout << endl;
}

void Load::_SetPossibleRoutes( Route r ) {

    for(size_t i = 0; i < r.GetEndCity()->GetFromShip().size(); i++)
    {
        cout << endl;
        cout << r.GetEndCity()->GetFromShip().size() << " ";
        cout << i+1<< " ";
        cout << r.GetEndCity()->GetFromShip()[i]->GetName() << " ";
        cout << r.GetEndCity()->GetFromShip()[i]->GetStartCity()->GetName() << " ";
        cout << r.GetEndCity()->GetFromShip()[i]->GetEndCity()->GetName() << endl;

        if( !r.Find(r.GetEndCity()->GetFromShip()[i]->GetEndCity()) )
        {
            int k = 0;

            cout << "Fordulo: " << k << ", fordulo erkezese: " << r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetEndDay() << ", bonuszido:  " << bonus_time << endl;

            while(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetEndDay() <= bonus_time && !IsReady())
            {
                cout << "Fordulo indulasa: " << r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetStartDay() << ", csomag erkezese: " << r.GetEndDay() << endl;

                if(r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetStartDay() >= r.GetEndDay())
                {
                    r.AddTurn(k,r.GetEndCity()->GetFromShip()[i]);

                    if(!r.IsFull())
                    {
                        if(r.GetEndCity() == to)routes.push_back(r);
                        else _SetPossibleRoutes(r);
                    }

                    r.DeleteTurn();
                }
                k=k+2;

                cout << "\nFordulo: " << k << ", fordulo erkezese: " << r.GetEndCity()->GetFromShip()[i]->GetTurn(k)->GetEndDay() << ", bonuszido:  " << bonus_time << endl;
            }
        }
    }
/*
    for(size_t i = 0; i < r.GetEndCity()->GetToShip().size(); i++)
    {
        cout << endl;
        cout << r.GetEndCity()->GetToShip().size() << " ";
        cout << i+1<< " ";
        cout << r.GetEndCity()->GetToShip()[i]->GetName() << " ";
        cout << r.GetEndCity()->GetToShip()[i]->GetStartCity()->GetName() << " ";
        cout << r.GetEndCity()->GetToShip()[i]->GetEndCity()->GetName() << endl;

        if( !r.Find(r.GetEndCity()->GetToShip()[i]->GetStartCity()) )
        {
            int k = 1;

            cout << "Fordulo: " << k << ", fordulo erkezese: " << r.GetEndCity()->GetToShip()[i]->GetTurn(k)->GetEndDay() << ", bonuszido:  " << bonus_time << endl;

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
    }*/
}
