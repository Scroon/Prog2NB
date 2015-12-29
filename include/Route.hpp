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
        bool TravellPass( City* c);
        bool IsWrong() { return wrong; }
        Route* Copy();

        void AddTurn( int turn_number, Ship* ship );
        void SetWrong() { wrong = true; }

    protected:


        Route(City * _from, City * _to, int _startday, int _endday, vector< pair< int, Ship* > > _turns);

        vector< pair< int, Ship* > > turns;

        bool wrong;

    private:
};

#endif // ROUTE_HPP
