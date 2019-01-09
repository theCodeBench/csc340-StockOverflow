#include "../catch.hpp"
#include "../../src/DataProvider/DataProvider.h"
#include "../../src/Market/Market.h"

TEST_CASE("Create a data provider") {
    DataProvider dataProvider;
}

TEST_CASE("Test loadStock method") {
    DataProvider dataProvider;
    Market market;
    int retVal = dataProvider.loadStock(market);
    REQUIRE(market.getSingleStock("googl").symbol.compare("googl") == 0);
    REQUIRE(retVal == 0);
}
