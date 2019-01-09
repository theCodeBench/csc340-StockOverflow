#include "AccountProvider.h"
#include <cstdlib>

int AccountProvider::storeAccount(Account account)
{
    ACCOUNTSFOLDER = getEnvironmentVariable("SO_AccountsDir");
    //Create a file for output
    ofstream outFile(ACCOUNTSFOLDER + "/" + accountFile);

    //Get a string representing the account
    string serialized = serializeAccount(account);

    //Check for successful serialization
    if(serialized == "")
    {
        return errorOutputs::ERROR_SERIALIZING;
    }

    //Write to the file
    outFile << serialized;
    outFile.close();
    return errorOutputs::SUCCESS;
}

Account AccountProvider::loadAccount(string accountId)
{
    //Try to open the account file
    ACCOUNTSFOLDER = getEnvironmentVariable("SO_AccountsDir");
    accountFile = ACCOUNT_FILE_TAG + accountId;
    ifstream inFile(ACCOUNTSFOLDER + "/" + accountFile);
    if(!inFile.is_open())
    {
        cerr << "Error opening account input file " << ACCOUNTSFOLDER << "/" << accountFile << endl;
        cerr << "Make sure you've set the SO_AccountsDir environment variable" << std::endl;
        Account emptyAccount;
        return emptyAccount;
    }

    //Deserialize that info into an account
    return deserializeAccount(inFile);
}

string AccountProvider::serializeAccount(Account account)
{
    string serialized = "";

    serialized += to_string(account.getCash());
    serialized += "\n";

    for(unsigned int i = 0; i < account.getOpenPositions().size(); i++)
    {
        OpenPosition position = account.getOpenPositions()[i];

        if(position.symbol.size() > 0 && position.count > 0)
        {
          serialized += position.symbol;
          serialized += ":" + to_string(position.buyPrice);
          serialized += ":" + to_string(position.count);
          serialized += ":" + to_string(position.dayOfPurchase);
          serialized += ":" + to_string(position.monthOfPurchase);
          serialized += ":" + to_string(position.yearOfPurchase);
          serialized += ":" + to_string(position.type);
          serialized += ":" + to_string(position.sellPrice);

          serialized += "\n";
        }
    }

    return serialized;
}


Account AccountProvider::deserializeAccount(ifstream &inFile)
{
    Account resultAcct;
    string line;

    //Get the cash line
    getline(inFile, line);

    resultAcct.addCash(stod(line));

    // Parse each line into the information
    while(getline(inFile, line))
    {
        char *cLine = new char [line.length()+1];
        strcpy(cLine, line.c_str());

        //Split by colons
        char * symbol = strtok (cLine,":");
        char * buyPrice = strtok (NULL, ":");
        char * count = strtok (NULL, ":");
        char * day = strtok (NULL, ":");
        char * month = strtok (NULL, ":");
        char * year = strtok (NULL, ":");
        char * type = strtok(NULL, ":");
        char * sellPrice = strtok(NULL,":");

        //Build an open position from the read in values
        OpenPosition position;
        position.symbol = symbol;
        position.buyPrice = atof(buyPrice);
        position.count = atoi(count);
        position.dayOfPurchase = atoi(day);
        position.monthOfPurchase = atoi(month);
        position.yearOfPurchase = atoi(year);
        position.sellPrice = atof(sellPrice);
        position.type = OpenPosition::SellType(atoi(type));

        //Add the open position to the account
        resultAcct.addOpenPosition(position);

        //Delete the dynamic cstring
        delete cLine;
    }

    return resultAcct;
}
