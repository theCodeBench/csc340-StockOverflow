#ifndef _TRADERHELPER_H_
#define _TRADERHELPER_H_

#include "../src/Trader/Trader.h"


void listAvailableStocks(Trader trader);
void buyStock(Trader trader);
void listOpenPositions(Trader trader);
void sellStock(Trader trader);
void displayCash(Trader trader);
void displayAccountValue(Trader trader);

#endif 
