#ifndef LOAD_HPP
#define LOAD_HPP

#include "Route.hpp"

#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include <fstream>

using namespace std;



struct CompareCommands
{
    int convertToInt( string s )
    {
        stringstream ss;
        int i;

        ss << s;
        ss >> i;

        ss.clear();

        return i;
    }

    bool operator() (string &lhs, string &rhs)
    {
        int e, m;

        for( size_t i = 0; i < lhs.length(); i++)
            if( lhs[i] == ' ' )
                e = CompareCommands::convertToInt(lhs.substr(0,i));

        for( size_t i = 0; i < rhs.length(); i++)
            if( rhs[i] == ' ' )
                m = CompareCommands::convertToInt(rhs.substr(0,i));

        if( e > m ) return true;
        else return false;
    }
};

class Load
{
    public:

        Load(const int _amount, const int _bonus_time, const string _name, City* _from, City* _to);
        virtual ~Load();

        int GetAmount() { return full_amount; }
        int GetID() const { return ID; }
        int GetFreeRouteNumber();

        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        void FindRoute(ofstream &o, int precision, bool out_bonus);
        void AddLoad(int &p);
        void GetCommands( priority_queue<string, vector<string>, CompareCommands> &all_commands);

        bool IsReady();
        bool GetPrecision(bool is_off, int precision, int turn_number, int bonus_multiply);

        static int NextID()
        {
            next_ID++;
            return next_ID;
        }

    protected:

        static int next_ID;

        int full_amount;
        int amount;
        int bonus_time;

        string name;

        City * from;
        City * to;

        int ID;

        vector< Route > routes;

        void FindRouteIn(Route &r, int precision, int bonus_multiply, bool out_bonus);
};

#endif // LOAD_HPP
