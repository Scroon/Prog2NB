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
        string GetName() const { return name; };
        vector<string> GetFromShipsName() const { return ships_name_from; }
        vector<string> GetToShipsName() const { return ships_name_to; }

    protected:

    string name;

    vector< string > ships_name_from;
    vector< string > ships_name_to;

    private:
};

#endif // CITY_HPP
