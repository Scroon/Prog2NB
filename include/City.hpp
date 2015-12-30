#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include <iostream>

using namespace std;

class Ship;

class City
{
    public:

        City(const string _name);

        virtual ~City();

        void AddToShip( Ship * s);
        void AddFromShip( Ship * s);

        string GetName() const { return name; };

        vector< Ship* > GetFromShip() const { return ships_from; }
        vector< Ship* > GetToShip() const { return ships_to; }

    protected:

    string name;

    vector< Ship* > ships_from;
    vector< Ship* > ships_to;

    private:
};

#endif // CITY_HPP
