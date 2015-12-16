#ifndef SHIP_HPP
#define SHIP_HPP

#include "Turn.hpp"

#include <vector>

using namespace std;

class Ship
{
    public:

        Ship();
        virtual ~Ship();

        Turn* GetTurn( const int index );

    protected:

        vector<Turn*> turns;

    private:
};

#endif // SHIP_HPP
