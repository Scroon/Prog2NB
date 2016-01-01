#include "Load.hpp"

Load::Load( const int _amount, const int _bonus_time, const string _name, City *_from, City *_to) : amount(_amount), bonus_time(_bonus_time), name(_name), from(_from), to(_to)
{
    ID = Load::NextID();
}

Load::~Load()
{

}

Load::MakeRoute(string city_from){

    Route* route = new Route(cities[city_from])

    void _MakeRoute(*route){



    }



}
