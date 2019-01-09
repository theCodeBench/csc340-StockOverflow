#include "Account.h"

double Account::getCash()
{
    return cash;
}

void Account::addCash(double value)
{
    cash += value;
}

vector<OpenPosition> Account::getOpenPositions()
{
    return openPositions;
}

void Account::addOpenPosition(OpenPosition position)
{
    openPositions.push_back(position);
}

int Account::removeOpenPosition(OpenPosition position, int count)
{
    int index = -100;
    //Find the position to remove
    for(unsigned int i = 0; i < openPositions.size(); i++)
    {
        //Compare positions
        if(openPositions[i].symbol == position.symbol
                && openPositions[i].buyPrice == position.buyPrice
                && openPositions[i].count == position.count
                && openPositions[i].dayOfPurchase == position.dayOfPurchase
                && openPositions[i].monthOfPurchase == position.monthOfPurchase
                && openPositions[i].yearOfPurchase == position.yearOfPurchase)
        {
            //Found it
            index = i;
            i = openPositions.size();
        }
    }


    if(index == -100)
    {
        return errorOutputs::OPEN_POSITION_NOT_FOUND;
    }

    //Make sure they aren't trying to remove more than they have
    if(openPositions[index].count < count)
    {
        return errorOutputs::COUNT_TOO_LARGE;
    }

    //If they sell all of this position then remove it from the list
    else if(openPositions[index].count == count)
    {
        openPositions.erase(openPositions.begin() + index);
    }

    //Otherwise just decrement their count
    else
    {
        openPositions[index].count -= count;
    }

    return errorOutputs::SUCCESS;
}

int Account::updatePositionType(OpenPosition position, int type, double price)
{
    int index = -100;
    double total = 0;
    //Find the position to remove
    for(unsigned int i = 0; i < openPositions.size(); i++)
    {
        //Compare positions
        if(openPositions[i].symbol == position.symbol
                && openPositions[i].buyPrice == position.buyPrice
                && openPositions[i].count == position.count
                && openPositions[i].dayOfPurchase == position.dayOfPurchase
                && openPositions[i].monthOfPurchase == position.monthOfPurchase
                && openPositions[i].yearOfPurchase == position.yearOfPurchase)
        {
            //Found it
            index = i;
            i = openPositions.size();
        }
    }


    if(index == -100)
    {
        return errorOutputs::OPEN_POSITION_NOT_FOUND;
    }
    else
    {
        if(openPositions[index].type == OpenPosition::SellType::DEFAULT)//adding type to default
        {
            openPositions[index].type = OpenPosition::SellType(type);
            openPositions[index].sellPrice = price;
            return errorOutputs::SUCCESS;
        }
        else if(openPositions[index].type == OpenPosition::SellType::LIMIT) //dont actually own positions
        {
            return errorOutputs::POSITION_TYPE_LIMIT;
        }
        else if(openPositions[index].type == OpenPosition::SellType::STOP_PROFIT)//both set already
        {
            return errorOutputs::POSITION_ALREADY_SET;
        }
        else if(openPositions[index].type == OpenPosition::SellType(type))//trying to add same thing
        {
            return errorOutputs::POSITION_ALREADY_SET;
        }
        else//adding additional type on either stop or profit
        {
            if(openPositions[index].type == OpenPosition::SellType::STOP)
            {
                total = (openPositions[index].sellPrice/(2+floor(log10(openPositions[index].sellPrice))));
                openPositions[index].sellPrice = price*100 + total + abs(log10(total/openPositions[index].sellPrice))*.1;
            }
            else if(openPositions[index].type == OpenPosition::SellType::PROFIT)
            {
                total = (price/(2+floor(log10(price))));
                openPositions[index].sellPrice = openPositions[index].sellPrice*100 + total + abs(log10(total/price))*.1;
            }

            openPositions[index].type = OpenPosition::SellType::STOP_PROFIT;
            return errorOutputs::SUCCESS;
        }

    }

}





