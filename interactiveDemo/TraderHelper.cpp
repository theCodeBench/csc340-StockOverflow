#include "TraderHelper.h"


void listAvailableStocks(Trader trader)
{
    map<string, Stock> stocks = trader.getAvailablePositions();

    for (map<string, Stock>::iterator it = stocks.begin(); it != stocks.end(); it++)
    {
        Stock stock = it->second;
        cout << stock.symbol << " : " << stock.h_end[0] << endl;
    }
}

void buyStock(Trader trader)
{
    map<string, Stock> stocks = trader.getAvailablePositions();
    string stockToBuy = stocks.begin()->second.symbol;
    cout <<"Buying: "<<stockToBuy<<" x5"<<endl;
    trader.buy(stockToBuy, 5);
}

void listOpenPositions(Trader trader)
{
    string sellType[6] = {"DEFAULT", "STOP", "LIMIT", "PROFIT", "STOP_PROFIT"};
    string tfPurchase[3] = {"True", "False"};
    vector<OpenPosition> ownedStocks = trader.getOpenPositions();

    cout << "\nShowing Owned Stocks" << endl;
    for (vector<OpenPosition>::iterator it = ownedStocks.begin(); it != ownedStocks.end(); it++)
    {
        OpenPosition currPos = *it;
        cout << sellType[currPos.type] << " " << currPos.symbol << " Buy:" << currPos.buyPrice << " x" 
            << currPos.count << " " << currPos.monthOfPurchase << "/" << currPos.dayOfPurchase 
            << "/" << currPos.yearOfPurchase << " Sell:" << currPos.sellPrice << endl;
            //" PurchasedToday:" << tfPurchase[currPos.notPurchasedToday] << endl;
    }
}

void sellStock(Trader trader)
{
    vector<OpenPosition> ownedStocks = trader.getOpenPositions();

    OpenPosition toSell = ownedStocks.back();

    cout << "\nSelling: " << toSell.symbol << " X" << toSell.count << " For:" << toSell.buyPrice << " each" << endl;
    trader.sell(toSell, toSell.count);
}

void displayCash(Trader trader)
{
  cout <<"\nCurrent Cash Level: "<< trader.getAccountCash()<<endl;
}

void displayAccountValue(Trader trader)
{
  cout <<"\nCurrent Account Value: "<< trader.getAccountValue()<<endl;
}
