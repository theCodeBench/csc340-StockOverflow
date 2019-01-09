#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"

TEST_CASE("Testing functionality when stop loss is not met")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    DataProvider data;
    Market market(data);
    string account = "Empty2";
    Broker broker(market, account);
    Trader trader(market, broker);
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
    CHECK(trader.createStopLoss(positionToCheck, 50) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 1);
    CHECK(broker.stopLoss(positionToCheck) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 1);
    CHECK(trader.getAccountCash() == cash);

   
    
}


TEST_CASE("Testing functionality when stop loss is met with open price")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    DataProvider data;
    Market market(data);
    string account = "Empty2";
    Broker broker(market, account);
    Trader trader(market, broker);
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
    CHECK(trader.createStopLoss(positionToCheck, 51.5) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    positionToCheck = positions.back();
    CHECK(positions.size() == 1);
    CHECK(positionToCheck.sellPrice == 51.5);
    CHECK(positionToCheck.symbol == "aal");
    CHECK(positionToCheck.count == 5);
    CHECK(positionToCheck.type == OpenPosition::SellType::STOP);
    CHECK(broker.stopLoss(positionToCheck) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 0);
    CHECK(trader.getAccountCash() > cash);

}


TEST_CASE("Testing functionality when stop loss is met with low price")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty2", ios::trunc);
    fout << "5000.000000";
    fout.close();

    DataProvider data;
    Market market(data);
    string account = "Empty2";
    Broker broker(market, account);
    Trader trader(market, broker);
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
    CHECK(trader.createStopLoss(positionToCheck, 51) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    positionToCheck = positions.back();
    CHECK(positions.size() == 1);
    CHECK(broker.stopLoss(positionToCheck) == errorOutputs::SUCCESS);
    positions = trader.getOpenPositions();
    CHECK(positions.size() == 0);
    CHECK(trader.getAccountCash() > cash);

}


