#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "Ship.hpp"

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Route
{
    public:

        Route(City * _from);
        virtual ~Route();

        bool Find ( City* c);
        bool IsFull();

        int GetCap();
        int GetFreeCap();

        int GetStartDay() const { return startday; }
        int GetEndDay() const { return endday; }

        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        int AddLoad(int amount, string name, int bonus);

        void AddTurn( int turn_number, Ship* ship );
        void DeleteTurn();

        vector< string > GetCommands() const { return commands; }

    protected:

        City * from;
        City * to;

        int startday;
        int endday;

        vector< Turn* > turns;
        vector< string > commands;
};

#endif // ROUTE_HPP
