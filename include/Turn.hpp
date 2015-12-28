#ifndef TURN_HPP
#define TURN_HPP

#include "City.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Turn
{
    public:
        Turn(City * _from, City * _to, const int _startday, const int _endday);
        virtual ~Turn();

        int GetTravellTime() const;
        int GetStartDay() const { return startday; }
        int GetEndDay() const { return endday; }
        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        virtual int GetPriority() const;

    protected:

        City * from;
        City * to;

        int startday;
        int endday;

        int priority;

    private:
};

#endif // TURN_HPP
