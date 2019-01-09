#include <iostream>
#include <vector>
#include <map>
#include "Trader.h"

void listStocks(std::map<std::string, OpenPosition> &portfolio)
{
   for (auto &kv : portfolio)
      std::cout << "Symbol: " << kv.first << " shares = " << kv.second.count << std::endl;
}

void showCash(Trader &trader)
{
   std::cout << trader.getAccountCash() << std::endl;
}

std::map<std::string, OpenPosition> fillPortfolio(Trader &trader)
{
   std::map<std::string, OpenPosition> portfolio;
   // Assumes there are no duplicates in the open positions
   for (OpenPosition position : trader.getOpenPositions())
         portfolio[position.symbol] = position;

   return portfolio;
}

void buyStock(std::string symbol, Trader &trader, int count)
{
   trader.buy(symbol, count);
}

int main()
{
   Trader trader("MyTradingAccount");
   std::map<std::string, OpenPosition> portfolio = fillPortfolio(trader);
   std::map<std::string, Stock> marketStocks = trader.getAvailablePositions();

   showCash(trader);
   listStocks(portfolio);

   if (marketStocks.find("nvda") != marketStocks.end())
      buyStock("nvda", trader, 20);

   showCash(trader);
   portfolio = fillPortfolio(trader);
   listStocks(portfolio); 
   return 0;
} 
