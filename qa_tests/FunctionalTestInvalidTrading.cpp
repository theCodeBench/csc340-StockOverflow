#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"


TEST_CASE("Functional test for trying to buy and sell invalid amounts of stocks")
{
    Trader trader("Invalid");

    double stockPriceGoog = trader.getStockPrice("goog");
    double stockPriceMsft = trader.getStockPrice("msft");
    vector<OpenPosition> myPositions = trader.getOpenPositions();

    //Uncomment in order to view current stock prices
    //listAvailableStocks(trader);

    //Check that we have 10 shares of Msft, and our cash = 5000
    CHECK(trader.getAccountCash() == 5000.00);
    OpenPosition myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);

    //Check that we can't buy too many expensive shares
    CHECK(trader.buy("goog", 5) == errorOutputs::NOT_ENOUGH_CASH);
    CHECK(trader.getAccountCash() == 5000.00 );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);

    //Check that we can't sell more stocks than we own
    CHECK(trader.sell(myPositionToSell, 11) == errorOutputs::COUNT_TOO_LARGE);
    CHECK(trader.getAccountCash() == 5000.00 );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);

    //Buy 0 stocks of goog
    CHECK(trader.buy("goog", 0) == errorOutputs::INVALID_AMOUNT_OF_STOCKS);
    CHECK(trader.getAccountCash() == 5000.00 );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);

    //Sell 0 stocks of msft
    CHECK(trader.sell(myPositionToSell, 0) == errorOutputs::INVALID_AMOUNT_OF_STOCKS);
    CHECK(trader.getAccountCash() == 5000.00 );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);

    //Buy negative stocks of goog
    CHECK(trader.buy("goog", -5) == errorOutputs::INVALID_AMOUNT_OF_STOCKS);
    CHECK(trader.getAccountCash() == 5000.00 );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);

    //Sell negative stocks of msft
    CHECK(trader.sell(myPositionToSell, -5) == errorOutputs::INVALID_AMOUNT_OF_STOCKS);
    CHECK(trader.getAccountCash() == 5000.00 );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "msft");
    CHECK(myPositionToSell.count == 10);


}
