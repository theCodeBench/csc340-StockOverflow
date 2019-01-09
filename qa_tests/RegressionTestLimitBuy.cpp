#include "Trader.h"
#include "TraderHelper.h"
#include "../tests/catch.hpp"

TEST_CASE("Don't allow unowned open positions to be sold")
{
    ofstream fout("ACCOUNTS_DIR/account_reg", ios::trunc);
    fout << "5000.000000";
    fout.close();
	
	DataProvider dataProvider;
	Market market(dataProvider);
	Broker broker(market, "reg");

    vector<OpenPosition> positions = broker.getOpenPositions();
    OpenPosition positionToCheck;
	double cash = broker.getAccountCash();
	int size = positions.size();

	CHECK(broker.createLimitBuy("aal", 2, 40) == errorOutputs::SUCCESS);
	CHECK(broker.getAccountCash() == cash);
	positions = broker.getOpenPositions();
    CHECK(positions.size() > 0);
	positionToCheck = positions.front();
	CHECK(positions.size() == size + 1);	
    CHECK(positionToCheck.type == OpenPosition::SellType::LIMIT);
	CHECK(broker.buyLimitOrder(positionToCheck.symbol, positionToCheck.count, positionToCheck.sellPrice) == errorOutputs::LIMIT_ORDER_NOT_MET); 

	for(OpenPosition position : positions)
    {
        if(position.type == OpenPosition::SellType::LIMIT)
        {
            if (broker.buyLimitOrder(position.symbol, position.count, position.sellPrice) == errorOutputs::SUCCESS)
            {
                Account account = AccountProvider::loadAccount("reg");
                account.removeOpenPosition(position, position.count);
                AccountProvider::storeAccount(account);
            }
            

        }
	}

 
	CHECK(broker.getAccountCash() == cash);
	
	CHECK(broker.sellStock(positionToCheck) == errorOutputs::OPEN_POSITION_NOT_OWNED);
	CHECK(broker.getAccountCash() == cash);

}



/*TEST_CASE("Allow open positions acquired from limit order to be sold")
{
    ofstream fout("ACCOUNTS_DIR/account_reg", ios::trunc);
    fout << "5000.000000";
    fout.close();

	DataProvider dataProvider;
	Market market(dataProvider);
	Broker broker(market, "reg");

    vector<OpenPosition> positions = broker.getOpenPositions();
    OpenPosition positionToCheck;
	double cash = broker.getAccountCash();
	int size = positions.size();

	CHECK(broker.createLimitBuy("aal", 2, 100) == errorOutputs::SUCCESS);
	CHECK(broker.getAccountCash() == cash);
	positions = broker.getOpenPositions();
	positionToCheck = positions.front();
	CHECK(positions.size() == size + 1);	
    CHECK(positionToCheck.type == OpenPosition::SellType::LIMIT);
	
	for(OpenPosition position : positions)
    {
        cout << position.symbol << ": " << position.type << endl; 
        if(position.type == OpenPosition::SellType::LIMIT)
        {
            cout << position.symbol << ": " << position.type << endl; 
            if (broker.buyLimitOrder(position.symbol, position.count, position.buyPrice)
                    == errorOutputs::SUCCESS)
            {
                cout << position.symbol << ": " << position.type << endl; 
                Account account = AccountProvider::loadAccount("reg");
                account.removeOpenPosition(position, position.count);
                AccountProvider::storeAccount(account);
                cout << "Bought " << position.symbol << endl;
            }

        }
	}
 
	CHECK(broker.getAccountCash() == cash - 2*51.45);
    positions = broker.getOpenPositions();
    CHECK(positions.size() == size + 1);

	positions = broker.getOpenPositions();
	positionToCheck = positions.front();
	CHECK(broker.sellStock(positionToCheck, 2, 51.45) == errorOutputs::SUCCESS);
	CHECK(broker.getAccountCash() == cash);
}
*/

