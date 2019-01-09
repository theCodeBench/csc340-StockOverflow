#include "../src/Trader/Trader.h"

void listAvailableStocks(Trader trader);
void buyStock(Trader trader);
void listOpenPositions(Trader trader);
void sellStock(Trader trader);

int main()
{
    Market market;
    string accountID = "Demo";
    Broker broker(market, accountID);
    Trader trader(market, broker);

    listAvailableStocks(trader);
    buyStock(trader);
    listOpenPositions(trader);
    sellStock(trader);
    listOpenPositions(trader);

    return 0;
}

void listAvailableStocks(Trader trader)
{
    map<string, Stock> stocks = trader.getAvailablePositions();

    for (map<string, Stock>::iterator it = stocks.begin(); it != stocks.end(); it++)
    {
        Stock stock = it->second;
        cout << stock.symbol << " : " << stock.currPrice << endl;
    }
}

void buyStock(Trader trader)
{
    map<string, Stock> stocks = trader.getAvailablePositions();
    string stockToBuy = stocks.begin()->second.symbol;

    trader.buy(stockToBuy, 5);
}

void listOpenPositions(Trader trader)
{
    vector<OpenPosition> ownedStocks = trader.getOpenPositions();

    cout << "\n\nShowing Owned Stocks" << endl;
    for (vector<OpenPosition>::iterator it = ownedStocks.begin(); it != ownedStocks.end(); it++)
    {
        OpenPosition currPos = *it;
        cout << currPos.symbol << " " << currPos.buyPrice << " " << currPos.count << endl;

    }
}

void sellStock(Trader trader)
{
    vector<OpenPosition> ownedStocks = trader.getOpenPositions();

    OpenPosition toSell = ownedStocks.back();

    cout << "\nSelling: " << toSell.symbol << " X" << toSell.count << " For:" << toSell.buyPrice << " each" << endl;
    trader.sell(toSell, toSell.count);
}
