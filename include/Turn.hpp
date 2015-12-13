#ifndef TURN_HPP
#define TURN_HPP

#include "City.hpp"
#include "Load.hpp"

#include <vector>

using namespace std;

class Turn
{
    public:
        Turn();
        virtual ~Turn();

        int GetTravellTime () const;
        int GetAllPrority() const;

        void AddLoad(Load *l);

    protected:

        vector< pair< int, Load* > >  loads;

        City * from;
        City * to;

        int startday;
        int endday;

    private:
};

#endif // TURN_HPP
