#include "Trader.h"

Trader::Trader(string accountID)
{
  DataProvider dataProvider;
  Market m(dataProvider);
  Broker b(m, accountID);
  market = m;
  broker = b;
}

void Trader::setAccountID(string account)
{
    broker.changeAccount(account);
}

string Trader::getAccountID()
{
    return broker.getAccount();
}

int Trader::createLimitBuy(string symbol, int shares, double price)
{
  return broker.createLimitBuy(symbol, shares, price);
}

int Trader::cancelLimitBuy(string symbol, int shares, double price)
{
  return broker.cancelLimitBuy(symbol, shares, price);
}

int Trader::buy(string symbol, int shares)
{
    return broker.buyStock(symbol, shares, -1);
}

int Trader::sell(OpenPosition openPosition, int shares)
{
    return broker.sellStock(openPosition, shares);
}

int Trader::sell(string symbol, int shares)
{
  vector<OpenPosition> openPositions = getOpenPositions();
  vector<OpenPosition>::iterator it = openPositions.begin();
  int status = errorOutputs::OPEN_POSITION_NOT_FOUND;

  while(it != openPositions.end() && shares > 0)
    {
      if (it->symbol == symbol && it->type == OpenPosition::SellType::DEFAULT)
	{
	  int curOPCount = it->count;
	  int numToSell = min(curOPCount, shares);
	  status = broker.sellStock(*it, numToSell);
	  shares -= curOPCount;
	}
      it++;
    }
  
  return status;
}

int Trader::createStopLoss(OpenPosition openPosition, double price)
{
    return broker.updatePositionType(openPosition, OpenPosition::SellType::STOP, price);
}

int Trader::cancelStopLoss(OpenPosition openPosition)
{
    return broker.updatePositionType(openPosition, OpenPosition::SellType::DEFAULT, 0);
}

int Trader::createTakeProfit(OpenPosition openPosition, double price)
{
    return broker.updatePositionType(openPosition, OpenPosition::SellType::PROFIT, price);
}

int Trader::cancelTakeProfit(OpenPosition openPosition)
{
  return broker.updatePositionType(openPosition, OpenPosition::SellType::DEFAULT, 0);
}

vector<OpenPosition> Trader::getOpenPositions()
{
    return broker.getOpenPositions();
}

map<string, Stock> Trader::getAvailablePositions()
{
    return broker.getAvailablePositions();
}

double Trader::getStockPrice(string symbol)
{
    return broker.getStockInfo(symbol).h_end[0];
}

double Trader::getAccountCash()
{
    return broker.getAccountCash();
}

double Trader::getAccountValue()
{
    return broker.getAccountValue();
}

Stock Trader::singleStock(string symbol)
{
    return market.getSingleStock(symbol);
}
