#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"


TEST_CASE("Functional tests for new sell type")
{
    ofstream fout("ACCOUNTS_DIR/account_Empty", ios::trunc);
    fout << "5000.000000";
    fout.close();

    Trader trader("Empty");
    vector<OpenPosition> myPositions = trader.getOpenPositions();
    double stockPrice = trader.getStockPrice("msft");

    CHECK(myPositions.empty() == true);
    CHECK(trader.getAccountCash() == 5000.00);

    CHECK(trader.buy("msft", 10) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (10.00*stockPrice)) );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);

    CHECK(trader.sell("msft", 10) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == 5000.00);
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 0);

    CHECK(trader.buy("msft", 10) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (10.00*stockPrice)) );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 1);


    CHECK(trader.buy("msft", 5) == errorOutputs::SUCCESS);
    //CHECK(trader.getAccountCash() == (5000.00 - (15.00*stockPrice)) );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 2);



    CHECK(trader.buy("msft", 1) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (16.00*stockPrice)) );
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 3);

    CHECK(trader.sell("msft", 7) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (9.00*stockPrice)));
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 3);
    CHECK(myPositions.at(0).count == 3);
    CHECK(myPositions.at(1).count == 5);
    CHECK(myPositions.at(2).count == 1);

    CHECK(trader.sell("msft", 4) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == (5000.00 - (5.00*stockPrice)));
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 2);
    CHECK(myPositions.at(0).count == 4);
    CHECK(myPositions.at(1).count == 1);
    
    CHECK(trader.sell("msft", 100) == errorOutputs::SUCCESS);
    CHECK(trader.getAccountCash() == 5000.00);
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 0);


    CHECK(trader.sell("aal", 100) == errorOutputs::OPEN_POSITION_NOT_FOUND);
    CHECK(trader.getAccountCash() == 5000.00);
    myPositions = trader.getOpenPositions();
    CHECK(myPositions.size() == 0);


}
