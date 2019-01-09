#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"


TEST_CASE("Check functionality for invalid limit buy")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty2");
    vector<OpenPosition> positions = trader.getOpenPositions();
    OpenPosition positionToCheck;
    int size = positions.size();
    double cash = trader.getAccountCash();

    //Make limit buy order that won't be met
    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(positions.size() == size);
    CHECK(trader.createLimitBuy("aal", 2, 40) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == size + 1);
    positionToCheck = positions.back();
    CHECK(positionToCheck.type == OpenPosition::SellType::LIMIT);
    CHECK(trader.getAccountCash() == cash);  
    positions = trader.getOpenPositions();
    CHECK(positions.size() == size + 1);

}

TEST_CASE("Check functionality for open price limit buy")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty2");
    vector<OpenPosition> positions = trader.getOpenPositions();
    OpenPosition positionToCheck;
    int size = positions.size();
    double cash = trader.getAccountCash();
    double cashTwo;

    //Make limit order that will buy at $51.45
    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(trader.createLimitBuy("aal", 2, 51.40) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == size + 1);
    positionToCheck = positions.back();
    CHECK(positionToCheck.type == OpenPosition::SellType::LIMIT);
    //CHECK(trader.getAccountCash() == cash - (2*positionToCheck.sellPrice));
    //cashTwo = cash - (2*positionToCheck.sellPrice);

    //Make a limit order that will buy at $52
    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(trader.createLimitBuy("aal", 2, 52) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
listOpenPositions(trader);
    CHECK(positions.size() == size + 2);
    positionToCheck = positions.back();
    CHECK(positionToCheck.type == OpenPosition::SellType::LIMIT);
    //CHECK(trader.getAccountCash() == cashTwo - (2*51.45));  
    positions = trader.getOpenPositions();
    //CHECK(trader.sell(positionToCheck) == errorOutputs::SUCCESS);
}


TEST_CASE("Check functionality for specified price limit buy")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty2");
    vector<OpenPosition> positions = trader.getOpenPositions();
    OpenPosition positionToCheck;
    int size = positions.size();
    double cash = trader.getAccountCash();

    //Make limit order that will buy at $51
    // aal open: 51.45  high: 51.88   low: 50.94   close: 51.67 
    CHECK(trader.createLimitBuy("aal", 2, 51) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == size + 1);
    positionToCheck = positions.back();
    CHECK(positionToCheck.type == OpenPosition::SellType::LIMIT);
    //CHECK(trader.getAccountCash() == cash - (2.0*positionToCheck.sellPrice));

}


