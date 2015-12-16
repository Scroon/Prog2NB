#ifndef LOAD_HPP
#define LOAD_HPP

#include "Route.hpp"

#include <vector>

using namespace std;

class Load
{
    public:

        Load();
        virtual ~Load();

    protected:

        int ID;

        vector<Route> routes;

    private:
};

#endif // LOAD_HPP
