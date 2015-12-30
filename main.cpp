
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



class Transport
{
public:
    Transport() {}

    void WriteCommands(){

        ofstream commands_file;
        commands_file.open(GetFileName().c_str());

        if(commands_file.good()){

            for(unsigned int i=0;i<commands.size();i++){

                commands_file << commands[i];

            }

        }

        commands_file.close

    }

    void ReadSchedule()
    {
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
                    s.push_back(str.substr(k,str.length()-k));

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
        else
        {
            cout << "\nHiba a fajl megnyitasakor!\n";
            ReadSchedule();
        }

        schedule.close();
    }

    void ReadCargo ()
    {
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
                    s.push_back(str.substr(k,str.length()-k));

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
        else
        {
            cout << "\nHiba a fajl megnyitasakor!\n";
            ReadCargo();
        }

        cargo.close();
    }

    void SetAllPossibleRoute ()
    {
        ofstream log;
        log.open("LOG.txt");

        if(comments.size() != 0) log << comments[0] << endl;

        for(size_t i = 0; i < 1; i++)
        {
            loads[10]->SetPossibleRoutes();
            loads[10]->WriteLog(log);
        }
    }

    void Teszt()
    {
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
    }

protected:

    map< string, City* > cities;
    map< string, Ship* > ships;
    vector< Load* > loads;
    vector<string> commands;
    vector<string> comments;

    string GetFileName() {
        string ret;
        cout << "\nKerem a fajlnevet!\n";
        cin >> ret;
        return ret;
    }
};

int Load::next_ID = -1;

int main()
{

    cout<<"Udvozoljuk a Marki_Kufcsak_Kovats Logisztikai Vallalatnal, TIHI ba a kiraly"<<endl;

    Transport TP;
    TP.ReadSchedule();
    TP.ReadCargo();
    TP.SetAllPossibleRoute();
    TP.WriteCommands();

    //TP.Teszt();


    return 0;
}
