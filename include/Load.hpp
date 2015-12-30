#ifndef LOAD_HPP
#define LOAD_HPP

#include "City.hpp"
#include "Route.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <functional>
#include <time.h>

using namespace std;

class Load
{
    public:

        Load(const int _amount, const int _bonus_time, const string _name, City* _from, City* _to);
        virtual ~Load();

        int GetID() const { return ID; }

        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        void FindRoute();
        void WriteLog(ofstream &o, priority_queue<string, vector<string>, greater<string> > &all_commands);

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
