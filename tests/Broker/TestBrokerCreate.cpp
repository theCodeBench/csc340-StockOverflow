#include "../catch.hpp"
#include "../../src/Broker/Broker.h"
#include "../../src/Accounts/AccountProvider.h"

TEST_CASE("Create a broker object with account name test") 
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market, "test");
}

