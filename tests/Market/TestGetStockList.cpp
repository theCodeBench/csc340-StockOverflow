#include "../catch.hpp"
#include "../../src/Market/Market.h"

TEST_CASE("Market Get Stock List")
{
    DataProvider dataProvider;
    Market market(dataProvider);

    map<string, Stock> stockList = market.getStockList();
}

TEST_CASE("Market Get Single Stock")
{
    DataProvider dataProvider;
    Market market(dataProvider);

    Stock singleStock = market.getSingleStock("aal");
    REQUIRE(singleStock.h_end[0] != -1);
}
