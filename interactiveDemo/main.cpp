#include "../src/Trader/Trader.h"
#include "TraderHelper.h"
#include <stdlib.h>
#include <algorithm>

void tradingMenu(Trader trader);
void displayMenu();
void clearScreen();


int main()
{
    DataProvider data;
    Market market(data);
    string accountID = "Demo";
    Broker broker(market, accountID);
    Trader trader(market, broker);

    tradingMenu(trader);

    return 0;
}

void tradingMenu(Trader trader)
{
    system("clear");

    cout << "-------------------------------------------------" << endl;
    cout << "- Welcome to Stock Overflow's trading platform! -" << endl;
    cout << "-------------------------------------------------" << endl;

    string userInput;
    string errorStrings[11] = {"SUCCESS","OPEN_POSITION_NOT_FOUND","COUNT TOO LARGE", 
"ERROR_SERIALIZING", "STOCK_DOESNT_EXIST", "NOT_ENOUGH_CASH", "LIMIT_ORDER_NOT_MET", 
"POSITION_TYPE_LIMIT", "POSITION_ALREADY_SET", "INVALID_AMOUNT_OF_STOCK"};

    do
    {
        cout << "What would you like to do today?\n";   //CHANGE NUMBERS TO ENUM EVENTUALLY
        displayMenu();
        cout << ">";
        cin >> userInput;

        //View Stocks
        if(userInput.compare("1") == 0)
        {
            listAvailableStocks(trader);
            clearScreen();
        }

        //View Open Positions
        else if(userInput.compare("2") == 0)
        {
            listOpenPositions(trader);
            clearScreen();
        }

        //Display Cash and Account Value
        else if(userInput.compare("3") == 0)
        {
            displayCash(trader);
            displayAccountValue(trader);
            clearScreen();
        }

        //Buy Stock
        else if(userInput.compare("4") == 0)
        {
            string buyStock;
            int buyAmount;

            cout << "\nStock Symbol: ";
            cin >> buyStock;
            cout << "Amount: ";
            cin >> buyAmount;

            int buyResult = trader.buy(buyStock, buyAmount);
            cout << errorStrings[buyResult] << endl;
            clearScreen();
        }

        //Sell Stock
        else if(userInput.compare("5") == 0)
        {
            string sellStock;
            int sellAmount;
            vector<OpenPosition> ownedStocks = trader.getOpenPositions();

            listOpenPositions(trader);
            
            if(ownedStocks.empty() == true)
            {
                cout << "No owned stocks available to sell\n" << endl;
            }

            else
            {
                cout << "\nStock Symbol: ";
                cin >> sellStock;
                cout << "Amount: ";
                cin >> sellAmount;

                vector<OpenPosition>::iterator it;

                //this code should probably be a function because it is useful
                it = find_if(ownedStocks.begin(), ownedStocks.end(),
                [sellStock] (const OpenPosition &pos) 
                {return pos.symbol == sellStock;}); 
                           
                OpenPosition sellPos = *it;

                if (it == ownedStocks.end())
                    cout << "You do not own that stock" << endl;
                else
                {
                    int sellResult = trader.sell(sellPos, sellAmount);
                    cout << errorStrings[sellResult] << endl;
                } 
         
            }
            
            clearScreen();
        }

        //Create Limit Buy
/*        else if(userInput.compare("6") == 0)
        {
            string buyStock;
            int buyAmount;
            double buyPrice;

            cout << "\nStock Symbol: ";
            cin >> buyStock;
            cout << "Amount: ";
            cin >> buyAmount;
            cout << "Price: ";
            cin >> buyPrice;

            int buyResult = trader.createLimitBuy(buyStock, buyAmount, buyPrice);
            cout << errorStrings[buyResult] << endl;
            clearScreen();
        }*/

        //Create Stop Loss
/*        else if(userInput.compare("7") == 0)
        {
            string stopLossStock;
            double stopLossPrice;
            vector<OpenPosition> ownedStocks = trader.getOpenPositions();

            listOpenPositions(trader);

            if(ownedStocks.empty() == true)
            {
                cout << "No owned stocks available to turn into stop loss\n" << endl;
            }

            else
            {
                cout << "\nStock: ";
                cin >> stopLossStock;
                cout << "Stop Loss Price: ";
                cin >> stopLossPrice;

                vector<OpenPosition>::iterator it;

                //this code should probably be a function because it is useful
                it = find_if(ownedStocks.begin(), ownedStocks.end(),
                [stopLossStock] (const OpenPosition &pos) 
                {return pos.symbol == stopLossStock;}); 
                
                OpenPosition stopLossPos = *it;

                if (it == ownedStocks.end())
                    cout << "You do not own that stock" << endl;
                else
                {
                    int result = trader.createStopLoss(stopLossPos, stopLossPrice);
                    cout << errorStrings[result] << endl;
                } 
         
            }


            clearScreen();
        }*/

        //Create Take Profit
/*        else if(userInput.compare("8") == 0)
        {
            cout << "Feature unavailable yet" << endl;

            string takeProfitStock;
            double takeProfitPrice;

            cout << "\nStock Symbol: ";
            cin >> takeProfitStock;
            cout << "Price: ";
            cin >> takeProfitPrice;

            trader.profitSale(takeProfitStock, takeProfitAmount, takeProfitPrice);

            clearScreen();
        }*/

        //Change Account
        else if(userInput.compare("9") == 0)
        {   
            string accountSwitch;

            cout << "Account to switch to: ";
            cin >> accountSwitch;
            trader.setAccountID(accountSwitch);
            clearScreen();
        }

        //Quit
        else if(userInput.compare("q") == 0)
        {
            exit(0);
        }

        else
        {
            system("clear");
        }



    }while(true);

}

void displayMenu()
{
    cout << "1. View current stocks" << endl;
    cout << "2. View my open positions" << endl;
    cout << "3. View my cash and account value" << endl;
    cout << "4. Buy stocks" << endl;
    cout << "5. Sell stocks" << endl;
//    cout << "6. Make limit buy order" << endl;
//    cout << "7. Make stop loss order" << endl;
//    cout << "8. Make take profit order" << endl;
    cout << "9. Change account" << endl;
    cout << "q. Quit" << endl;
}

void clearScreen()
{
    char garbageEntry = 'a';
    cout << "\nPress enter to continue " << endl;
    cin.ignore();
    while(garbageEntry != '\n')
        cin.get(garbageEntry);
    system("clear");
}







