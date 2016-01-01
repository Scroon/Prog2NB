#ifndef LOAD_HPP
#define LOAD_HPP

#include "Route.hpp"

#include <vector>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

class Load
{
    public:

        Load(const int _amount, const int _bonus_time, const string _name, City* _from, City* _to);
        virtual ~Load();

        int GetID() const { return ID; }
        int GetFreeRouteNumber();

        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        void FindRoute();
        void AddLoad();
        void GetCommands( priority_queue<string, vector<string>, greater<string> > &all_commands);

        bool IsReady();

        static int NextID()
        {
            next_ID++;
            return next_ID;
        }

    protected:

        static int next_ID;

        int amount;
        int bonus_time;

        string name;

        City * from;
        City * to;

        int ID;

        vector< Route > routes;

        void FindRouteIn( Route r, int &t);
};

#endif // LOAD_HPP
