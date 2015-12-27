
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

                getline(schedule,str);
            }

        }
        else
        {
            cout << "\nHiba a fajl megnyitasakor!\n";
        }

        schedule.close();
    }

    void Teszt()
    {
        cout << cities.size() << endl;
        cout << ships.size() << endl;
    }

protected:

    map< string, City* > cities;
    map< string, Ship* > ships;
    map< int, Load* > loads;

    string GetFileName() {
        string ret;
        cout << "\nKerem a a fajlnevet!\n";
        cin >> ret;
        return ret;
    }
};

int Load::next_ID = 0;

int main()
{

    cout<<"Udvozoljuk a Marki_Kufcsak_Kovats Logisztikai Vallalatnal, TIHI ba a kiraly"<<endl;

    Transport TP;
    TP.ReadSchedule();

    TP.Teszt(); //hajók és a városok száma


    return 0;
}
