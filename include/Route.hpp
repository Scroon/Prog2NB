#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "Ship.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Route
{
    public:
        Route();
        virtual ~Route();

        int GetRoutePriority();


    protected:

        vector< pair< int, Ship* > > turns;

    private:
};

#endif // ROUTE_HPP
