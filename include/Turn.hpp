#ifndef TURN_HPP
#define TURN_HPP

#include "City.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Load;

class Turn
{
    public:
        Turn(City * _from, City * to, const int _startday, const int endday);
        virtual ~Turn();

        int GetTravellTime () const;
        int GetAllPriority() const;

        void AddLoad();

    protected:

        City * from;
        City * to;

        int startday;
        int endday;

        int priority;

    private:
};

#endif // TURN_HPP
