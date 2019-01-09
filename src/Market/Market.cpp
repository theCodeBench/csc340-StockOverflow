#include "Market.h"

Market::Market()
{
}

Market::Market(DataProvider &data) {
    dataProvider = data;
    stocks = dataProvider.getStocks();
}

int Market::buyStock(Account &currAccount, string symbol, int count, double price)
{
    //if stock doesn't exist
    if(!stocks.count(symbol))
    {
        return errorOutputs::STOCK_DOESNT_EXIST;
    }

    if(count <= 0)
    {
        return errorOutputs::INVALID_AMOUNT_OF_STOCKS;
    }
    double money;
    if(price < 0)
        money = stocks[symbol].h_end.at(0);
    else
        money = price;
    //if user doesn't have enough cash
    if(currAccount.getCash() < count*money)
    {
        return errorOutputs::NOT_ENOUGH_CASH;
    }
    //remove cash from account
    currAccount.addCash(-count*money);

    //add open position to account
    OpenPosition newPurchase;
    newPurchase.symbol = symbol;
    newPurchase.buyPrice = money;
    newPurchase.count = count;
    time_t t = time(0);
    struct tm* now = localtime(&t);
    newPurchase.dayOfPurchase = now->tm_mday;
    newPurchase.monthOfPurchase = now->tm_mon+1;
    newPurchase.yearOfPurchase = now->tm_year + 1900;
    currAccount.addOpenPosition(newPurchase);
    return errorOutputs::SUCCESS;
}

int Market::createLimitBuy(Account &account, OpenPosition &position)
{
    if(!stocks.count(position.symbol))
    {
        return errorOutputs::STOCK_DOESNT_EXIST;
    }
    account.addOpenPosition(position);
    return errorOutputs::SUCCESS;
}

int Market::cancelLimitBuy(Account &account, OpenPosition &position, int count)
{
  account.removeOpenPosition(position, count);
  return errorOutputs::SUCCESS;
}

int Market::sellStock(Account &currAccount, OpenPosition position, int shares, double price)
{

    if(shares <= 0)
    {
        return errorOutputs::INVALID_AMOUNT_OF_STOCKS;
    }

	if(position.type == OpenPosition::SellType::LIMIT)
	{
		return errorOutputs::OPEN_POSITION_NOT_OWNED;
	}

    int status = currAccount.removeOpenPosition(position,shares);
    if(status== errorOutputs::SUCCESS) {

        double money;
        //Regular sale use end of Day price
        if(price < 0)
        {
            money = shares*stocks[position.symbol].h_end.at(0);
        }
        //Special Sell (StopLoss For Profit etc.)
        else
        {
            money = shares*price;
        }

        currAccount.addCash(money);

    }
    return status;
}

map<string, Stock> Market::getStockList()
{
    return stocks;
}

Stock Market::getSingleStock(string symbol)
{
    //if stock exists, return stock
    if(stocks.count(symbol))
    {
        return stocks[symbol];
    }
    cerr << symbol << " was not found in the market.\n";
    Stock didntFind;
    didntFind.h_end[0] = -1;
    return didntFind;
}


int Market::updatePositionType(Account &currAccount, OpenPosition position, int type, double price)
{
    int status = currAccount.updatePositionType(position, type, price);
    return status;
}
