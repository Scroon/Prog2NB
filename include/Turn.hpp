#ifndef TURN_HPP
#define TURN_HPP

#include "City.hpp"

#include <vector>
#include <iostream>

using namespace std;

class Ship;

class Turn
{
    public:
        Turn( Ship * _ship, City * _from, City * _to, const int _startday, const int _endday, const int _capacity);
        virtual ~Turn();

        Ship* GetShip() { return ship; }

        int GetCap() { return capacity; }
        int GetFreeCap() { return capacity - used_cap; }

        int GetStartDay() const { return startday; }
        int GetEndDay() const { return endday; }

        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

        void AddLoad(int amount);

        bool IsFull();

    protected:

        Ship * ship;

        City * from;
        City * to;

        int startday;
        int endday;

        int capacity;
        int used_cap;
};

#endif // TURN_HPP
