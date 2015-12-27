#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include <iostream>

using namespace std;

class City
{
    public:

        City(const string _name);

        virtual ~City();

        void AddToShip( const string name);
        void AddFromShip( const string name);

    protected:

    string name;

    vector< string > ships_name_from;
    vector< string > ships_name_to;

    private:
};

#endif // CITY_HPP
