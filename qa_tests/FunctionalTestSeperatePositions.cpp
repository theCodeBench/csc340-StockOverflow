#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"


TEST_CASE("Functional test for buying single stocks and hoping they consolidate.  ")
{
    Trader trader("Seperate");

    double stockPrice = trader.getStockPrice("v");

    vector<OpenPosition> myPositions = trader.getOpenPositions();

    //Uncomment in order to view current stock prices
    //listAvailableStocks(trader);

    CHECK(myPositions.size() == 2);

    //Buy a single stock five times
    //This newest stock should consolidate into one stock of 5 shares
    for(int i = 1; i <= 5; i++)
    {
        CHECK(trader.buy("v", 1) == errorOutputs::SUCCESS);
        myPositions = trader.getOpenPositions();
        CHECK(myPositions.size() == 3);
        OpenPosition myPositionToSell = myPositions.back();
        CHECK(myPositionToSell.symbol == "v");
        CHECK(myPositionToSell.count == i);
    }

    //Sell all of the consolidated stocks
    OpenPosition myPositionToSell = myPositions.at(3);
    CHECK(trader.sell(myPositionToSell, 5) == errorOutputs::SUCCESS);
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 2);
    myPositionToSell = myPositions.front();
    CHECK(myPositionToSell.symbol == "v");
    CHECK(myPositionToSell.count == 15);
    CHECK(myPositionToSell.dayOfPurchase == 20);
    CHECK(myPositionToSell.buyPrice == 100.00);      
  
    myPositionToSell = myPositions.back();
    CHECK(myPositionToSell.symbol == "v");
    CHECK(myPositionToSell.count == 10); 
    CHECK(myPositionToSell.dayOfPurchase == 21);
    CHECK(myPositionToSell.buyPrice == 110.00);            
    

}
