#include "../catch.hpp"
#include "../../src/DataProvider/DataProvider.h"
#include "../../src/Stocks/Stock.h"

TEST_CASE("Load the stocks")
{
    DataProvider dataProvider;
    map<string, Stock> loadedStocks = dataProvider.getStocks();
}


