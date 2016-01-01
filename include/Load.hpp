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
    bool operator() (string &lhs, string &rhs)
    {
        if( lhs > rhs ) return true;
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

        void FindRoute(ofstream &o, int p);
        void FindRouteOutBonus();
        void AddLoad(int &p);
        void GetCommands( priority_queue<string, vector<string>, CompareCommands> &all_commands);

        bool IsReady();

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

        void FindRouteIn( Route &r, int p );
        void FindRouteOutBonusIn( Route &r );
};

#endif // LOAD_HPP
