#include "../catch.hpp"
#include "../../src/Broker/Broker.h"
#include "../../src/Market/Market.h"

TEST_CASE("Get stock price from market") 
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");

    Stock singleStock = broker.getStockInfo("aal");  //Try the first stock

    REQUIRE(singleStock.h_end[0] > 0);
}

TEST_CASE("Get open positions info from account provider") 
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");

    broker.getOpenPositions();
}

TEST_CASE("Get available positions from the market")
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");

    map<string, Stock> availablePositions = broker.getAvailablePositions();
}

TEST_CASE("Get available cash from account")
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "default");
    
    REQUIRE(broker.getAccountCash() == 1000);
    
}

TEST_CASE("Get the value of an account")
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");
    
    broker.getAccountValue();
}
