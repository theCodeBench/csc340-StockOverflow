#include "../catch.hpp"
#include "../../src/Broker/Broker.h"
#include "../enumErrorOutputs.h"

TEST_CASE("Check that account provider has available funds")
{
    //Unneeded?
}

TEST_CASE("Check that market data provider has available positions")
{
    //Unneeded?
}

TEST_CASE("Buy stock for account purchase request")
{
    ofstream fout("ACCOUNTS_DIR/account_test", ios::trunc);
    fout << "1000.000000\ngoog:500.000000:50:6:10:2016:0:0";
    fout.close();

    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");

    REQUIRE(broker.buyStock("aal", 5)  == errorOutputs::SUCCESS);
}

TEST_CASE("Sell stock for account sell request")
{
    ofstream fout("ACCOUNTS_DIR/account_test", ios::trunc);
    fout << "1000.000000\ngoog:500.000000:50:6:10:2016:0:0";
    fout.close();

    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");
    
    OpenPosition openPosition = broker.getOpenPositions().at(0);
    REQUIRE(broker.sellStock(openPosition, 2)  == errorOutputs::SUCCESS);    
}

TEST_CASE("Change account ID")
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");
    broker.changeAccount("default");
    REQUIRE(broker.getAccountCash() == 1000);
}

TEST_CASE("Implement a limit order buy")
{  
    ofstream fout("ACCOUNTS_DIR/account_test", ios::trunc);
    fout << "12000.000000\ngoog:550.000000:50:6:10:2016:0:0";			//set google to trade at 550
    fout.close();

    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");
    
    //try to buy 5 shares with limit specified price of $0 -> limit order will not be met
    REQUIRE(broker.buyLimitOrder("goog", 5, 0) == errorOutputs::LIMIT_ORDER_NOT_MET);
   
    //try to buy 5 shares with limit specified price of $1065 -> should be able to buy
   //tests when limit price specified is less than low
    REQUIRE(broker.buyLimitOrder("goog", 5, 1065)  == errorOutputs::SUCCESS);

    //try to buy 4 shares with limit specified price of $1080 -> should be able to buy
   //tests when limit price specified is less than end
    REQUIRE(broker.buyLimitOrder("goog", 4, 1080)  == errorOutputs::SUCCESS);

    //try to buy 2 shares with limit specified price of $1075 -> should be able to buy
   //tests when limit price specified is less than start
    REQUIRE(broker.buyLimitOrder("goog", 2, 1075)  == errorOutputs::SUCCESS);

    //try to buy 7 shares with limit specified price of 1080 and not enough cash in account
    REQUIRE(broker.buyLimitOrder("goog", 7, 1080) == errorOutputs::NOT_ENOUGH_CASH);

}
