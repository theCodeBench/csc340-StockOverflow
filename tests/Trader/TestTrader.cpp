#include "../catch.hpp"
#include "../../src/Trader/Trader.h"
#include "../../src/enumErrorOutputs.h"

TEST_CASE("Initialize Trader")
{
  Trader trader("test");
}

TEST_CASE("Get Available Positions")
{

  Trader trader("test");

    map<string, Stock> stocks = trader.getAvailablePositions();
    REQUIRE(stocks.empty() != true);
}

TEST_CASE("Buy a Stock")
{
    Trader trader("test");

    map<string, Stock> stocks = trader.getAvailablePositions();
    REQUIRE(stocks.empty() != true);

    string symbol = stocks.begin()->second.symbol;

    REQUIRE(trader.buy(symbol, 1) == errorOutputs::SUCCESS);
}

TEST_CASE("Get Open Positions")
{
    Trader trader("test");

    vector<OpenPosition> openPositions = trader.getOpenPositions();
    REQUIRE(openPositions.empty() != true);
}


TEST_CASE("Sell a Stock")
{
    Trader trader("test");

    vector<OpenPosition> openPositions = trader.getOpenPositions();
    REQUIRE(openPositions.empty() != true);

    OpenPosition oneToSell = openPositions.back();

    REQUIRE(trader.sell(oneToSell, oneToSell.count) == errorOutputs::SUCCESS);
}

TEST_CASE("Get Stock Price")
{
    Trader trader("test");

    map<string, Stock> stocks = trader.getAvailablePositions();
    REQUIRE(stocks.empty() != true);

    string symbol = stocks.begin()->second.symbol;

    double stockPrice = trader.getStockPrice(symbol);

    REQUIRE(stockPrice > 0);
}

TEST_CASE("Trader can change the account the broker uses")
{
    Trader trader("test");
    trader.setAccountID("default");
    REQUIRE(trader.getAccountCash() == 1000);

}

TEST_CASE("Trader can cancel stop loss")
{
    Trader trader("test");

    vector<OpenPosition> openPositions = trader.getOpenPositions();

    REQUIRE (openPositions.empty() != true);

    OpenPosition testPosition = openPositions.back();
    REQUIRE(trader.createStopLoss(testPosition, (int)(testPosition.buyPrice / 2)) == errorOutputs::SUCCESS);

    REQUIRE (trader.cancelStopLoss(testPosition) == errorOutputs::SUCCESS);

}

TEST_CASE("Cancel a Take Profit order")
{
  Trader trader("test");
  
  vector<OpenPosition> openPositions = trader.getOpenPositions();
  REQUIRE (openPositions.empty() != true);
  
  OpenPosition takeProfitPosition = openPositions.back();

  REQUIRE( trader.createTakeProfit(takeProfitPosition, 100000)
   == errorOutputs::SUCCESS);

  REQUIRE (trader.cancelTakeProfit(takeProfitPosition) == errorOutputs::SUCCESS);
 
}

TEST_CASE("Trader can cancel limit buy")
{
  Trader trader("testCancelLimit");

  trader.createLimitBuy("aapl", 2, 100.00);

  vector<OpenPosition> openPositions = trader.getOpenPositions();
  REQUIRE(openPositions.empty() != true);

  trader.cancelLimitBuy("aapl", 2, 100.00);

  openPositions = trader.getOpenPositions();

  REQUIRE(openPositions.empty() == true);
}
