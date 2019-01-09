#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"

TEST_CASE("Don't include empty stock data")
{
    Trader trader("Empty");
       
    map<string, Stock> positions = trader.getAvailablePositions();

    for(auto x: positions)
    {
        cout << x.first << endl;
        CHECK(!x.second.h_start.empty());
        CHECK(!x.second.h_high.empty());
        CHECK(!x.second.h_low.empty());
        CHECK(!x.second.h_end.empty());
        CHECK(!x.second.h_volume.empty());
    }
    
}
