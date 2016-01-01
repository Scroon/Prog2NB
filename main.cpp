
#include "City.hpp"
#include "Load.hpp"
#include "Route.hpp"
#include "Turn.hpp"
#include "Ship.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>
#include <exception>

using namespace std;

int convertToInt( string s )
{
    stringstream ss;
    int i;

    ss << s;
    ss >> i;

    ss.clear();

    return i;
}

struct CompareLoad
{
    bool operator() (Load * lhs, Load * rhs)
    {
        if(lhs->GetFreeRouteNumber() > rhs->GetFreeRouteNumber()) return true;
        else return false;
    }
};

class Transport
{
public:
    Transport() {}

    void WriteCommands()
    {

        cout << "\nA rakodasi utasitasok kiirasa.\n";

        ofstream commands_file;
        commands_file.open(GetFileName().c_str());

        if(commands_file.good()){

            if(comments.size() != 0) commands_file << comments[0] << endl;

            while(!commands.empty()) {
                commands_file << commands.top() << endl;
                commands.pop();
            }
        }
        else throw 2;

        commands_file.close();
    }

    void ReadSchedule()
    {
        cout << "\nA menetrendet tartalmazo fajl beolvasasa.\n";

        ifstream schedule;
        schedule.open(GetFileName().c_str());

        string str;

        if(schedule.good()) {

            getline(schedule,str);

            while(!schedule.eof())
            {
                if( str[0] != '#' )
                {
                    vector<string> s;

                    int k = 0;
                    for( size_t i = 0; i < str.length(); i++)
                    {
                        if( str[i] == ' ' )
                        {
                            s.push_back(str.substr(k,i-k));
                            k = i+1;
                        }
                    }
                    s.push_back(str.substr(k));

                    if(s.size() < 7) throw 1;
/*
                    cout << endl;
                    cout << s[0] << endl;
                    cout << s[1] << endl;
                    cout << s[2] << endl;
                    cout << s[3] << endl;
                    cout << s[4] << endl;
                    cout << s[5] << endl;
                    cout << s[6] << endl;
                    cout << endl;
*/


                    if( cities.find(s[2]) == cities.end() ) {
                        cities[s[2]] = new City(s[2]);
                    }

                    if( cities.find(s[3]) == cities.end() ) {
                        cities[s[3]] = new City(s[3]);
                    }

                    Ship * ship = new Ship(s[0],cities.find(s[2])->second,cities.find(s[3])->second,convertToInt(s[6]),convertToInt(s[4]),convertToInt(s[5]),convertToInt(s[1]));

                    ships[s[0]] = ship;
                    ship->AddToCity();
                }
                else comments.push_back(str);

                getline(schedule,str);
            }

        }
        else throw 2;

        schedule.close();
    }

    void ReadCargo()
    {
        cout << "\nA rakomanyokat tartalmazo fajl beolvasasa.\n";

        ifstream cargo;
        cargo.open(GetFileName().c_str());

        string str;

        if(cargo.good()) {

            getline(cargo,str);

            while(!cargo.eof())
            {
                if( str[0] != '#' )
                {
                    vector<string> s;

                    int k = 0;
                    for( size_t i = 0; i < str.length(); i++)
                    {
                        if( str[i] == ' ' )
                        {
                            s.push_back(str.substr(k,i-k));
                            k = i+1;
                        }
                    }
                    s.push_back(str.substr(k));

                    if(s.size() < 5) throw 1;

/*
                    cout << endl;
                    cout << s[0] << endl;
                    cout << s[1] << endl;
                    cout << s[2] << endl;
                    cout << s[3] << endl;
                    cout << s[4] << endl;
                    cout << endl;
*/

                    Load * load = new Load(convertToInt(s[1]),convertToInt(s[4]),s[0],cities.find(s[2])->second,cities.find(s[3])->second);

                    loads.push_back(load);
                }
                else comments.push_back(str);

                getline(cargo,str);
            }
        }
        else throw 2;

        cargo.close();
    }

    void FindRoute()
    {
        for(size_t i = 0; i < 10; i++)
        {
            loads[i]->FindRoute();
        }

        for(size_t i = 0; i < 10; i++)
        {
            if(loads[i]->GetFreeRouteNumber() != 0) in_bonus.push(loads[i]);
            else out_bonus.push_back(loads[i]);
        }
    }

    void SetRoute()
    {
        in_bonus.top()->AddLoad();
        in_bonus.top()->GetCommands(commands);

        if(in_bonus.top()->IsReady()) in_bonus.pop();

        priority_queue<Load*, vector<Load*>, CompareLoad> temporary;

        size_t k = in_bonus.size();
        for(size_t i = 0; i < k; i++)
        {
            if(in_bonus.top()->GetFreeRouteNumber() != 0) temporary.push(in_bonus.top());
            else out_bonus.push_back(in_bonus.top());

            in_bonus.pop();
        }

        in_bonus = temporary;

        if(!in_bonus.empty()) SetRoute();
    }

    void GetStruct()
    {
        cout << "\nA tarolt informaciok lekerese.\n";

        for( size_t j = 0; j < loads.size(); j++)
        {
            cout << loads[j]->GetStartCity()->GetName() << endl;
            cout << endl;

            for( size_t i = 0; i < cities.find(loads[j]->GetStartCity()->GetName())->second->GetFromShip().size(); i++)
            {
                cout << cities.find(loads[j]->GetStartCity()->GetName())->second->GetFromShip()[i]->GetName() << "  ";
                cout << cities.find(loads[j]->GetStartCity()->GetName())->second->GetFromShip()[i]->GetStartCity()->GetName() << "  ";
                cout << cities.find(loads[j]->GetStartCity()->GetName())->second->GetFromShip()[i]->GetEndCity()->GetName() << endl;
                cout << endl;
            }
            for( size_t i = 0; i < cities.find(loads[j]->GetStartCity()->GetName())->second->GetToShip().size(); i++)
            {
                cout << cities.find(loads[j]->GetStartCity()->GetName())->second->GetToShip()[i]->GetName() << "  ";
                cout << cities.find(loads[j]->GetStartCity()->GetName())->second->GetToShip()[i]->GetStartCity()->GetName() << "  ";
                cout << cities.find(loads[j]->GetStartCity()->GetName())->second->GetToShip()[i]->GetEndCity()->GetName() << endl;
                cout << endl;
            }
        }

        cout << endl;
        cout << cities.size() << endl;
        cout << ships.size() << endl;
        cout << loads.size() << endl;
        cout << "\nA bonusz idon belul celba nem jutott rakomanyok szama: " << out_bonus.size() << "\n";

    }

protected:

    map< string, City* > cities;
    map< string, Ship* > ships;

    vector< Load* > loads;
    vector< Load* > out_bonus;

    vector< string > comments;

    priority_queue<Load*, vector<Load*>, CompareLoad> in_bonus;
    priority_queue<string, vector<string>, greater<string> > commands;

    string GetFileName()
    {
        string ret;
        cout << "Kerem a fajlnevet: ";
        cin >> ret;
        return ret;
    }
};

int Load::next_ID = -1;

int main()
{
    try
    {
        cout<<"Udvozoljuk a Marki_Kufcsak_Kovats Logisztikai Vallalatnal, TIHI ba a kiraly"<<endl;

        Transport TP;
        TP.ReadSchedule();
        TP.ReadCargo();
        TP.FindRoute();
        TP.SetRoute();
        TP.WriteCommands();
        TP.GetStruct();

        cout << "\nA program sikeresen befejezte futasat.\n";
    }
    catch (int e) { cout << "\nAn exception occurred. Exception Nr. " << e << "\nThe program shuts down!\n"; }
    catch (exception& e) { cout << "\nAn exception occurred. Exception: " << e.what() << "\nThe program shuts down!\n"; }

    return 0;
}
