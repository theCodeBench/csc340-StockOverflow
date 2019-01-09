#include "Broker.h"

using namespace std;

Broker::Broker()
{}

Broker::Broker(Market &m, string account): accountId(account), market(m)
{
    dailyOperations();
}

void Broker::changeAccount(string account)
{
    accountId = account;
}

string Broker::getAccount()
{
    return accountId;
}

int Broker::buyStock(string symbol, int shares, double price) {
    Account account = AccountProvider::loadAccount(accountId); //Get account from provider with id
    int status = market.buyStock(account, symbol, shares, price); //Send account to market with symbol, return success
    AccountProvider::storeAccount(account);
    return status;
}

int Broker::sellStock(OpenPosition openPosition, int shares, double price) {
    Account account = AccountProvider::loadAccount(accountId); //Get account from provider
	//if(openPosition.type == OpenPosition::SellType::LIMIT)
		//return errorOutputs::OPEN_POSITION_NOT_OWNED;
    int status = market.sellStock(account, openPosition,shares,price); //Send account to market with symbol and return success
    AccountProvider::storeAccount(account);
    return status;
}

int Broker::takeProfit(OpenPosition openPosition)
{
    Stock dailyInfo = getStockInfo(openPosition.symbol);
    int status;

    if(dailyInfo.h_start[0] >= openPosition.sellPrice)
    {
        //sell at Open Price
        status = sellStock(openPosition,openPosition.count,dailyInfo.h_start[0]);
    }
    else if(dailyInfo.h_high[0] <= openPosition.sellPrice)
    {
        //sell at market price end
        status = sellStock(openPosition,openPosition.count,dailyInfo.h_end[0]);
    }
    else
    {
        status = errorOutputs::SUCCESS;
    }
    return status;
}

int Broker::buyLimitOrder(string symbol, int shares, double price)
{
    Stock info = getStockInfo(symbol);

    //if the start value is less than or equal than the price, buy at start value
    if(info.h_start[0] <= price)
        return buyStock(symbol, shares, info.h_start[0]);

    //if the low or end values are less than or equal to the price
    else if(info.h_low[0] <= price ||  info.h_end[0] <= price)
        return buyStock(symbol, shares, price);	//buy the stock at the limit specified price

    else
        return errorOutputs::LIMIT_ORDER_NOT_MET;	//otherwise return error
}

int Broker::createLimitBuy(string symbol, int shares, double price)
{
    Account account = AccountProvider::loadAccount(accountId);
    OpenPosition position;
    position.symbol = symbol;
    position.type = OpenPosition::SellType::LIMIT;
    position.sellPrice = 0;
    position.buyPrice = price;
    position.count = shares;

    //when adding limits, there is no date of purchase because it has
    //not been purchased. Function to remove checks for date later
    //default date is 0/0/0

    position.dayOfPurchase = 0;
    position.monthOfPurchase = 0;
    position.yearOfPurchase = 0;

    int status = market.createLimitBuy(account, position);
    if (status == errorOutputs::SUCCESS)
        AccountProvider::storeAccount(account);
    return status;
}

int Broker::cancelLimitBuy(string symbol, int shares, double price)
{
    Account account = AccountProvider::loadAccount(accountId);
    OpenPosition position;
    position.symbol = symbol;
    position.type = OpenPosition::SellType::LIMIT;
    position.sellPrice = 0;
    position.buyPrice = price;
    position.count = shares;

    //see comment in create limit buy
    position.dayOfPurchase = 0;
    position.monthOfPurchase = 0;
    position.yearOfPurchase = 0;

    int status = market.cancelLimitBuy(account, position, shares);
    if (status == errorOutputs::SUCCESS)
        AccountProvider::storeAccount(account);
    return status;
}

int Broker::stopLoss(OpenPosition openPosition)
{
    Stock dailyInfo = getStockInfo(openPosition.symbol);
    int status;

    if(dailyInfo.h_start[0] <= openPosition.sellPrice)
    {
        //sell at Open Price
        status = sellStock(openPosition,openPosition.count,dailyInfo.h_start[0]);
    }
    else if(dailyInfo.h_low[0] <= openPosition.sellPrice)
    {
        //sell at sellPrice
        status = sellStock(openPosition,openPosition.count,openPosition.sellPrice);
    }
    else
    {
        status = errorOutputs::SUCCESS;
    }
    return status;
}

Stock Broker::getStockInfo(string symbol) 
{
    Stock info = market.getSingleStock(symbol); //Get stock info from market with symbol
    return info; //Print out symbol and price
}

int Broker::updatePositionType(OpenPosition position, int type, double price)
{
    Account account = AccountProvider::loadAccount(accountId);
    int status = market.updatePositionType(account, position, type,price);
    if (status == SUCCESS)
        AccountProvider::storeAccount(account);
    return status;
}

vector<OpenPosition> Broker::getOpenPositions()
{
    Account account = AccountProvider::loadAccount(accountId); //Load account from provider
    return account.getOpenPositions();
}

map<string, Stock> Broker::getAvailablePositions() 
{
    return market.getStockList(); //Get map of available stocks
}

double Broker::getAccountCash() 
{
    Account account = AccountProvider::loadAccount(accountId); //Load account from provider
    return account.getCash();
}

double Broker::getAccountValue() 
{
    Account account = AccountProvider::loadAccount(accountId); //Load account from provider
    double value = account.getCash();
    Stock stock;

    for(unsigned int i = 0; i < account.getOpenPositions().size(); i++)
    {
        OpenPosition position = account.getOpenPositions()[i];

        stock = market.getSingleStock(position.symbol);
        value += (stock.h_end.at(0) * position.count);
    }

    return value;
}

void Broker::dailyOperations()
{
    vector<OpenPosition> positions = getOpenPositions();
    for(OpenPosition position : positions)
    {
        if(position.type == OpenPosition::SellType::LIMIT)
        {
            if (buyLimitOrder(position.symbol, position.count, position.sellPrice)
                    == errorOutputs::SUCCESS)
            {
                Account account = AccountProvider::loadAccount(accountId);
                account.removeOpenPosition(position, position.count);
                AccountProvider::storeAccount(account);
            }

        }
        else if(position.type == OpenPosition::SellType::STOP)
        {
            stopLoss(position);
        }
        else if(position.type == OpenPosition::SellType::PROFIT)
        {
            takeProfit(position);
        }
        else if(position.type == OpenPosition::SellType::STOP_PROFIT)
        {
            double profit = floor(position.sellPrice)/100;
            double loss = position.sellPrice - profit;
            int lossShift = floor(loss*10);
            loss = loss - floor(loss*10)/10;
            loss *= pow(10,lossShift);
            srand(time(0));

            Stock stock = getStockInfo(position.symbol);
            if(stock.h_start[0]> stock.h_end[0])  //take profit hit first
            {
                position.sellPrice = profit;
                if(position.sellPrice < stock.h_start[0])
                {
                    takeProfit(position);
                }
                else if(position.sellPrice > stock.h_start[0])
                {
                    if(rand()%4)
                    {
                        takeProfit(position);
                    }
                    else
                    {
                        position.sellPrice = loss;
                        stopLoss(position);
                    }
                }
            }
            else if(stock.h_start[0] <= stock.h_end[0])//stoploss will be hit first
            {
                position.sellPrice = loss;
                if(position.sellPrice > stock.h_start[0])
                {
                    stopLoss(position);
                }
                else if(position.sellPrice < stock.h_start[0])
                {
                    if(rand()%4)
                    {
                        stopLoss(position);
                    }
                    else
                    {
                        position.sellPrice = profit;
                        takeProfit(position);
                    }
                }
            }
        }
    }
}
