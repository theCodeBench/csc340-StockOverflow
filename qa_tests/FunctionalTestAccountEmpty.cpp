#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"


TEST_CASE("Functional test for starting with only money, but no open positions.  ")
{
    Trader trader("Empty");

    double stockPrice = trader.getStockPrice("msft");
    vector<OpenPosition> myPositions = trader.getOpenPositions();

    //Uncomment in order to view current stock prices
    //listAvailableStocks(trader);

    //Check that we do not have any positions, and our cash = 5000
    CHECK(myPositions.empty() == true);
    CHECK(trader.getAccountCash() == 5000.00);

    //Check that we can buy shares and that they were added
    CHECK(trader.buy("msft", 10) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (10.00*stockPrice)) );
    myPositions = trader.getOpenPositions();
    OpenPosition myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.buyPrice == stockPrice);
    CHECK(myPositionToSell.count == 10);

    //Check that we can sell half of our stocks and that they were removed
    CHECK(trader.sell(myPositionToSell, 5) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (5.00*stockPrice)) );
    myPositions = trader.getOpenPositions();
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.buyPrice == stockPrice);
    CHECK(myPositionToSell.count == 5);

    //Check that we can sell the rest of our stocks
    CHECK(trader.sell(myPositionToSell, 5) == errorOutputs::SUCCESS);
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.empty() == true);
    CHECK(trader.getAccountCash() == 5000.00);




}
