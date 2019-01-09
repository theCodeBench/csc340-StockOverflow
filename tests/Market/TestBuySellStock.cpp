#include "../catch.hpp"
#include "../../src/Market/Market.h"
#include "../../src/Broker/Broker.h"
#include "../../src/Accounts/Account.h"
#include "../../src/Accounts/AccountProvider.h"

TEST_CASE("Test Market Buy Stock")
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Account account = Account(10000);

    market.buyStock(account, "aal", 5);
}

TEST_CASE("Test Market Sell Stock")
{
    DataProvider dataProvider;
    Market market(dataProvider);
    Broker broker(market);
    
    Account account = Account(10000);
    OpenPosition openPosition;

    market.buyStock(account, "aal", 11);
    openPosition = account.getOpenPositions().at(0);

    market.sellStock(account, openPosition);
}
