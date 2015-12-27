#include "City.hpp"

City::City(const string _name) : name(_name)
{
    //ctor
}

City::~City()
{
    //dtor
}

void City::AddToShip( const string name)
{
    ships_name_to.push_back(name);
}

void City::AddFromShip( const string name)
{
    ships_name_from.push_back(name);
}
