#include "../../src/Accounts/Account.h"
#include "../../src/Accounts/AccountProvider.h"
#include "../catch.hpp"
#include "../enumErrorOutputs.h"

TEST_CASE("AccountProvider storeAccount() method with an open position")
{
    Account account(1000);
    
    OpenPosition testPosition;
    testPosition.symbol = "GOOGL";
    testPosition.buyPrice = 100;
    testPosition.count = 50;
    testPosition.dayOfPurchase = 6;
    testPosition.monthOfPurchase = 10;
    testPosition.yearOfPurchase = 2016;
    
    account.addOpenPosition(testPosition);
    
    REQUIRE(AccountProvider::storeAccount(account) == errorOutputs::SUCCESS);
}

TEST_CASE("AccountProvider loadAccount() method with an open position")
{
    Account account(1000);
    
    OpenPosition testPosition;
    testPosition.symbol = "GOOGL";
    testPosition.buyPrice = 500;
    testPosition.count = 50;
    testPosition.dayOfPurchase = 6;
    testPosition.monthOfPurchase = 10;
    testPosition.yearOfPurchase = 2016;
    
    account.addOpenPosition(testPosition);
    
    REQUIRE(AccountProvider::storeAccount(account)  == errorOutputs::SUCCESS);
    
    Account loaded = AccountProvider::loadAccount("default");
    
    //Validate the loaded in fields
    REQUIRE(loaded.getCash() == account.getCash());
    REQUIRE(loaded.getOpenPositions().size() == account.getOpenPositions().size());
    
    REQUIRE(loaded.getOpenPositions()[0].symbol == account.getOpenPositions()[0].symbol);
    REQUIRE(loaded.getOpenPositions()[0].buyPrice == account.getOpenPositions()[0].buyPrice);
    REQUIRE(loaded.getOpenPositions()[0].count == account.getOpenPositions()[0].count);
    REQUIRE(loaded.getOpenPositions()[0].dayOfPurchase == account.getOpenPositions()[0].dayOfPurchase);
    REQUIRE(loaded.getOpenPositions()[0].monthOfPurchase == account.getOpenPositions()[0].monthOfPurchase);
    REQUIRE(loaded.getOpenPositions()[0].yearOfPurchase == account.getOpenPositions()[0].yearOfPurchase);
}
















