
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
    Transport() : profit(0), price(10), price_bonus(30) { log.open("log.txt"); }
    ~Transport() { log.close(); }

    void WriteCommands()
    {
        for(size_t i = 0; i < loads.size(); i++)
        {
            loads[i]->GetCommands(instruction);
        }

        cout << "\nA rakodasi utasitasok kiirasa.\n";

        ofstream commands;
        commands.open(GetFileName().c_str());

        if(commands.good()){

            if(comments.size() != 0) commands << comments[0] << endl;

            while(!instruction.empty()) {
                commands << instruction.top() << endl;
                instruction.pop();
            }
        }
        else throw 2;

        commands.close();
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
        cout << "\nAdd meg az utvonalakereses pontossagat: \n(pl.: 3, 83%-os celba jutas bonuszidon belul, futasido kb. 5 perc) ";
        cin >> precision_index;

        if(comments.size() != 0) log << comments[0] << endl;

        GetStruct();

        for(size_t i = 0; i < loads.size(); i++)
        {
            cout << "\nRakomany Nr. " << i << " Calculating...\n";
            loads[i]->FindRoute(log, precision_index, false);
        }

        for(size_t i = 0; i < loads.size(); i++)
        {
            if(loads[i]->GetFreeRouteNumber() != 0) in_bonus.push(loads[i]);
            else out_bonus.push(loads[i]);
        }

        cout << "\nA varosok szama: " << cities.size();
        cout << "\nA hajok szama: " << ships.size();
        cout << "\nA rakomanyok szama: " << loads.size();
        cout << "\nA pontossagi index: " << precision_index << endl;
        cout << "\nBonusz idon belul celba nem jutatthato rakomanyok szama: " << out_bonus.size() << endl;

        log << "\nA varosok szama: " << cities.size();;
        log << "\nA hajok szama: " << ships.size();
        log << "\nA rakomanyok szama: " << loads.size();
        log << "\nA pontossagi index: " << precision_index << endl;
        log << "\nBonusz idon belul celba nem jutatthato rakomanyok szama: " << out_bonus.size();
    }

    void SetRoute()
    {
        cout << "\nPreparation of Instructions In Bonus Time ...\n";

        while(!in_bonus.empty())
        {
            in_bonus.top()->AddLoad(profit);

            if(in_bonus.top()->IsReady()) in_bonus.pop();

            priority_queue<Load*, vector<Load*>, CompareLoad> temporary;

            while(!in_bonus.empty())
            {
                if(in_bonus.top()->GetFreeRouteNumber() != 0) temporary.push(in_bonus.top());
                else out_bonus.push(in_bonus.top());

                in_bonus.pop();
            }

            in_bonus = temporary;
        }

        log << "\nBonusz idon belul celba nem jutott rakomanyok szama: " << out_bonus.size() << endl;

        cout << "\nBonusz idon belul celba nem jutott rakomanyok szama: " << out_bonus.size() << endl;

        cout << "\nPreparation of Instructions Out Bonus Time ...\n";

        while(!out_bonus.empty())
        {
            out_bonus.front()->FindRoute(log,precision_index,true);
            out_bonus.front()->AddLoad(profit);

            if(out_bonus.front()->IsReady()) out_bonus.pop();
        }

        log << endl;
        log << "\nCelba nem jutott rakomanyok szama: " << out_bonus.size() << endl;
        log << "\nA profit: " << profit << endl;

        cout << "\nCelba nem jutott rakomanyok szama: " << out_bonus.size() << endl;
        cout << "\nA profit: " << profit << endl;
    }

    void GetStruct()
    {
        for( size_t j = 0; j < loads.size(); j++)
        {
            log << loads[j]->GetStartCity()->GetName() << endl;
            log << endl;

            for( size_t i = 0; i < cities[loads[j]->GetStartCity()->GetName()]->GetFromShip().size(); i++)
            {
                log << cities[loads[j]->GetStartCity()->GetName()]->GetFromShip()[i]->GetName() << "  ";
                log << cities[loads[j]->GetStartCity()->GetName()]->GetFromShip()[i]->GetStartCity()->GetName() << "  ";
                log << cities[loads[j]->GetStartCity()->GetName()]->GetFromShip()[i]->GetEndCity()->GetName() << endl;
                log << endl;
            }
            for( size_t i = 0; i < cities.find(loads[j]->GetStartCity()->GetName())->second->GetToShip().size(); i++)
            {
                log << cities[loads[j]->GetStartCity()->GetName()]->GetToShip()[i]->GetName() << "  ";
                log << cities[loads[j]->GetStartCity()->GetName()]->GetToShip()[i]->GetStartCity()->GetName() << "  ";
                log << cities[loads[j]->GetStartCity()->GetName()]->GetToShip()[i]->GetEndCity()->GetName() << endl;
                log << endl;
            }
        }
    }

protected:

    ofstream log;

    int profit;
    int price;
    int price_bonus;
    int precision_index;

    map< string, City* > cities;
    map< string, Ship* > ships;

    vector< Load* > loads;
    vector< string > comments;

    queue<Load*> out_bonus;

    priority_queue<Load*, vector<Load*>, CompareLoad> in_bonus;
    priority_queue<string, vector<string>, CompareCommands> instruction;

    string GetFileName()
    {
        string ret;
        cout << "Kerem a fajlnevet: ";
        cin >> ret;
        return ret;
    }

    int convertToInt( string s )
    {
        stringstream ss;
        int i;

        ss << s;
        ss >> i;

        ss.clear();

        return i;
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

        cout << "\nA program sikeresen befejezte futasat.\n";
    }
    catch (int e) { cout << "\nAn exception occurred. Exception Nr. " << e << "\nThe program shuts down!\n"; }

    return 0;
}
