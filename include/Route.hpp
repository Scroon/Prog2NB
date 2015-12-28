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

        int GetPriority() const;

        void AddTurn( int turn_number, Ship* ship );

    protected:

        vector< pair< int, Ship* > > turns;

    private:
};

#endif // ROUTE_HPP
