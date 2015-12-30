#ifndef TURN_HPP
#define TURN_HPP

#include "City.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Turn
{
    public:
        Turn(City * _from, City * _to, const int _startday, const int _endday, const int _capacity);
        virtual ~Turn();

        int GetCap() { return capacity; }
        int GetStartDay() const { return startday; }
        int GetEndDay() const { return endday; }
        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        void AddLoad( int amount );

        virtual int GetFreeCap() { return capacity - used_cap; }
        virtual bool IsFull();

    protected:

        City * from;
        City * to;

        int startday;
        int endday;
        int capacity;
        int used_cap;

    private:
};

#endif // TURN_HPP
