#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "Ship.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Route : public Turn
{
    public:
        Route(City * _from, City * _to, const int _startday, const int _endday);
        virtual ~Route();

        int GetRoutePriority();


    protected:

        vector< pair< int, Ship* > > turns;

    private:
};

#endif // ROUTE_HPP
