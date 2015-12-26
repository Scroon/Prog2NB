#ifndef LOAD_HPP
#define LOAD_HPP

#include "Route.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Load
{
    public:

        Load(const int _amount, const int _bonus_time, const string _name, City* _from, City* _to);
        virtual ~Load();

    protected:

        static int last_ID;

        int amount;
        int bonus_time;

        string name;

        City * from;
        City * to;

        int ID;

        vector<Route> routes;

    private:
};

int Load::last_ID = -1;

#endif // LOAD_HPP
