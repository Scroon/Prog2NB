#ifndef SHIP_HPP
#define SHIP_HPP

#include "Turn.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Ship
{
    public:

        Ship();
        virtual ~Ship();

        Turn* GetTurn( const int index );

    protected:

        string name;

        City * from;
        City * to;

        int startday;
        int days_there;
        int days_back;

        vector<Turn*> turns;

    private:
};

#endif // SHIP_HPP
