#ifndef SHIP_HPP
#define SHIP_HPP

#include "City.hpp"
#include "Turn.hpp"

#include <map>
#include <iostream>

using namespace std;

class Ship
{
    public:

        Ship(const string _name, City* &_from, City* &_to, const int _startday, const int _days_there, const int _days_back, const int _capacity);
        virtual ~Ship();

        Turn* GetTurn( const size_t index );

        void AddToCity();
        string GetName() { return name; }
        City* GetStartCity() { return from; }
        City* GetEndCity() { return to; }

    protected:

        string name;

        City * from;
        City * to;

        int startday;
        int days_there;
        int days_back;
        int capacity;

        map< int, Turn* > turns;

    private:
};

#endif // SHIP_HPP
