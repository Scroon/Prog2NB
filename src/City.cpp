#include "City.hpp"

City::City(const string _name) : name(_name)
{
    //ctor
}

City::~City()
{
    //dtor
}

void City::AddToShip( Ship * s)
{
    ships_to.push_back(s);
}

void City::AddFromShip( Ship * s)
{
    ships_from.push_back(s);
}
