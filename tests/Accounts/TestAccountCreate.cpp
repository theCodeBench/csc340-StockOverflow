#include "../../src/Accounts/Account.h"
#include "../catch.hpp"
#include <vector>

using namespace std;

TEST_CASE("Account generic constructor")
{
    Account account;
}

TEST_CASE("Account constructor with cash param")
{
    Account account(1000);
}

TEST_CASE("Account constructor with cash and open position list params")
{
    vector<OpenPosition> positions;
    
    OpenPosition testPosition;
    testPosition.symbol = "GOOGL";
    testPosition.buyPrice = 100;
    testPosition.count = 50;
    
    positions.push_back(testPosition);
    
    Account account(1000, positions);
}




