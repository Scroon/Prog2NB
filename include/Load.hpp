#ifndef LOAD_HPP
#define LOAD_HPP

#include "City.hpp"
#include "Route.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Load
{
    public:

        Load(const int _amount, const int _bonus_time, const string _name, City* _from, City* _to);
        virtual ~Load();

        int GetID() const { return ID; }

        bool IsReady();

        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        void SetPossibleRoutes();
        void WriteLog(ofstream &o);

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

        bool ready;

        vector< Route > routes;
        vector< string > commands;

        void _SetPossibleRoutes( Route r );

    private:
};

#endif // LOAD_HPP
