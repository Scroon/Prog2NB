#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "Ship.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Route : public Turn
{
    public:
        Route(City * _from);
        virtual ~Route();

        bool Find ( City* c);
        bool IsFull ();

        int AddLoad(int amount);
        int GetFreeCap();

        void AddTurn( int turn_number, Ship* ship );
        void DeleteTurn();

    protected:

        vector< Turn* > turns;


    private:
};

#endif // ROUTE_HPP
