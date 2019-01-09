#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"

TEST_CASE("Testing functionality when take profit is not met")//////////////
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty2");
    vector<OpenPosition> positions = trader.getOpenPositions();
    OpenPosition positionToCheck;
    double cash;

    REQUIRE(positions.size() == 0);
    CHECK(trader.buy("aal", 5) == errorOutputs::SUCCESS);
    cash = trader.getAccountCash();
    positions = trader.getOpenPositions();
    REQUIRE(positions.size() == 1);
    positionToCheck = positions.back();
cout << "1" << endl;
listOpenPositions(trader);
    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(trader.createTakeProfit(positionToCheck, 52) == errorOutputs::SUCCESS);//value too high to sell
    positions = trader.getOpenPositions();
cout << "2" << endl;
listOpenPositions(trader);
    CHECK(positions.size() == 1);
    CHECK(broker.takeProfit(positionToCheck) == errorOutputs::SUCCESS);///
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 1);
    CHECK(trader.getAccountCash() == cash);
cout << "3" << endl;
listOpenPositions(trader);
   
    
}


TEST_CASE("Testing functionality when take profit is met with open price")/////////
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty2");
    vector<OpenPosition> positions = trader.getOpenPositions();
    OpenPosition positionToCheck;
    double cash;

    REQUIRE(positions.size() == 0);
    CHECK(trader.buy("aal", 5) == errorOutputs::SUCCESS);
    cash = trader.getAccountCash();
    positions = trader.getOpenPositions();
    REQUIRE(positions.size() == 1);
    positionToCheck = positions.back();

    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(trader.createTakeProfit(positionToCheck, 51.5) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    positionToCheck = positions.back();
    CHECK(positions.size() == 1);
    CHECK(positionToCheck.sellPrice == 51.5);
    CHECK(positionToCheck.symbol == "aal");
    CHECK(positionToCheck.count == 5);
    CHECK(positionToCheck.type == OpenPosition::SellType::PROFIT);
    CHECK(broker.takeProfit(positionToCheck) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 0);
    CHECK(trader.getAccountCash() > cash);

}


TEST_CASE("Testing functionality when take profit is met with low price")/////////////
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty2");
    vector<OpenPosition> positions = trader.getOpenPositions();
    OpenPosition positionToCheck;
    double cash;

    REQUIRE(positions.size() == 0);
    CHECK(trader.buy("aal", 5) == errorOutputs::SUCCESS);
    cash = trader.getAccountCash();
    positions = trader.getOpenPositions();
    REQUIRE(positions.size() == 1);
    positionToCheck = positions.back();


    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(trader.createTakeProfit(positionToCheck, 51) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    positionToCheck = positions.back();
    CHECK(positions.size() == 1);
    CHECK(broker.takeProfit(positionToCheck) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 0);
    CHECK(trader.getAccountCash() > cash);

}


