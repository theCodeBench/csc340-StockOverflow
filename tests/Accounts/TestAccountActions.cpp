#include "../../src/Accounts/Account.h"
#include "../catch.hpp"
#include <vector>

TEST_CASE("Account getCash")
{
    Account account(9000);
    
    REQUIRE(account.getCash() == 9000);
}

TEST_CASE("Account addCash")
{
    Account account(1000);
    
    account.addCash(50);
    REQUIRE(account.getCash() == 1050);
    
    account.addCash(-500);
    REQUIRE(account.getCash() == 550);
    
    account.addCash(0);
    REQUIRE(account.getCash() == 550);
}

TEST_CASE("Account getOpenPositions")
{
    vector<OpenPosition> positions;
    OpenPosition testPosition;
    testPosition.symbol = "GOOGL";
    testPosition.buyPrice = 100;
    testPosition.count = 50;
    
    positions.push_back(testPosition);
    
    Account account(1000, positions);
    
    REQUIRE(account.getOpenPositions().size() == 1);
}

TEST_CASE("Account addOpenPosition")
{
    Account account(1000);
    
    OpenPosition testPosition;
    testPosition.symbol = "GOOGL";;
    testPosition.buyPrice = 100;
    testPosition.count = 50;
    
    account.addOpenPosition(testPosition);
    
    REQUIRE(account.getOpenPositions().size() == 1);
}

TEST_CASE("Account removeOpenPosition")
{
    OpenPosition testPosition;
    testPosition.symbol = "GOOGL";;
    testPosition.buyPrice = 100;
    testPosition.count = 50;
    testPosition.dayOfPurchase = 1;
    testPosition.monthOfPurchase = 1;
    testPosition.yearOfPurchase = 2018;
    
    OpenPosition anotherPosition;
    anotherPosition.symbol = "AAPL";
    anotherPosition.buyPrice = 200;
    anotherPosition.count = 25;
    testPosition.dayOfPurchase = 4;
    testPosition.monthOfPurchase = 7;
    testPosition.yearOfPurchase = 2012;
   
    Account account(1000);
    account.addOpenPosition(testPosition);
    account.addOpenPosition(anotherPosition);
    
    REQUIRE(account.removeOpenPosition(account.getOpenPositions()[0], 50) == 0);
    REQUIRE(account.getOpenPositions().size() == 1);
    REQUIRE(account.getOpenPositions()[0].symbol == "AAPL");
    
    REQUIRE(account.removeOpenPosition(account.getOpenPositions()[0], 10) == 0);
    REQUIRE(account.getOpenPositions().size() == 1);
    REQUIRE(account.getOpenPositions()[0].count == 15);
}




