#include "DataProvider.h"

DataProvider::DataProvider()
{
    loadStocks();
}

// Helper function for DataProvider::loadStocks
//
// Return environment variable
std::string getEnvironmentVariable(std::string const &key)
{
   char *val = getenv(key.c_str());
   return val == NULL ? std::string("") : std::string(val);
}

void DataProvider::loadStocks()
{
    ifstream fin;
    std::string stockFilePath = getEnvironmentVariable("SO_StockData");
    fin.open(stockFilePath);
    // Check for error in opening file
    if(!fin)
    {
        std::cerr << "Error opening SO_StockData [" << stockFilePath << "]" << std::endl;
        std::cerr << "Make sure you've set the SO_StockData environment variable" << std::endl;
        return;
    }

    Stock stock;
    string currStock;
    vector<double> histinfo;

    while(fin >> currStock)
    {
        // If the line contains '{' it is the stock name
        if(currStock.find("{") != string::npos)
        {
            stock.symbol = currStock.substr(0, currStock.find("{"));
            // If the line does not contain '}' then it is relevant data
        }

        else if (currStock.find("}") == string::npos)
        {
            histinfo = parseHistory(currStock);
            stock.h_start.push_back(histinfo[0]);
            stock.h_high.push_back(histinfo[1]);
            stock.h_low.push_back(histinfo[2]);
            stock.h_end.push_back(histinfo[3]);
            stock.h_volume.push_back(int(histinfo[4]));
            // '}' symbol is the last possibility which triggers
            // storage of the Stock object into the map
        }

        else
        {
            if(!stock.h_start.empty() || !stock.h_high.empty() || !stock.h_low.empty() || !stock.h_end.empty() || !stock.h_volume.empty())
            {
                stocks.emplace(stock.symbol, stock);
            }
            stock.h_start.clear();
            stock.h_high.clear();
            stock.h_low.clear();
            stock.h_end.clear();
            stock.h_volume.clear();
        }
    }
}

/*
 * Private function used for code succinctness
 */
vector<double> DataProvider::parseHistory(string line)
{
    vector<double> retvec;

    line = line.substr(line.find(":") + 1, line.length());
    // Start
    retvec.push_back(stod(line.substr(0, line.find(":"))));
    line = line.substr(line.find(":") + 1, line.length());
    // High
    retvec.push_back(stod(line.substr(0, line.find(":"))));
    line = line.substr(line.find(":") + 1, line.length());
    // Low
    retvec.push_back(stod(line.substr(0, line.find(":"))));
    line = line.substr(line.find(":") + 1, line.length());
    // End
    retvec.push_back(stod(line.substr(0, line.find(":"))));
    line = line.substr(line.find(":") + 1, line.length());
    // Volume
    retvec.push_back(stod(line.substr(0, line.find(":"))));

    return retvec;
}

map<string, Stock> DataProvider::getStocks()
{
    return stocks;
}
