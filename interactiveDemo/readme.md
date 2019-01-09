Usage: run "make"
       run ./main

Enter a number 1-9 to run the chosen option.
Enter in 'q' to quit the program.

Menu description:
1: View current stocks 
    Uses the TraderHelper's listAvailableStocks function to call 
    the Trader's getAvailablePositions function and iteratively 
    display each stock.

2: View historical stock
    Unavailable until branch is merged to develop

3: View my open positions
    Uses the TraderHelper's listOpenPositions function to call 
    the Trader's getOpenPositions function and iteratively 
    display each position.

4: View my cash and account value
    Uses the TraderHelper's displayCash function to call and
    display the Trader's getAccountCash function.  The same happens
    with the getAccountValue function.

5: Buy stocks
    Prompts the user for a stock symbol and an amount of stock to buy.
    Uses the TraderHelper's buyStock function.
    -- Error codes are invalid until bugs are merged. --

6: Sell stocks
    Prompts the user for a stock symbol and an amount of stock to sell.
    The stock must be apart of your owned stocks in order for you to
    sell a stock.
    -- Currently it sells the first occurance of a stock symbol. --
    -- Error codes are invalid until bugs are merged. --

7: Make limit buy order
    Unavailable until branch is merged to develop

8: Make stop loss order
    Unavailable until branch is merged to develop

9: Make take profit order
    Unavailable until branch is merged to develop

