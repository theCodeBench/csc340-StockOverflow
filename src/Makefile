LIBRARYNAME = libPlatform.so

SOURCE = Account.cpp \
         AccountProvider.cpp \
         Broker.cpp \
         DataProvider.cpp \
         Market.cpp \
         Trader.cpp

OBJS = $(SOURCE:.cpp=.o)

GCC = g++

LINK = g++

AR = ar rs

INC = -IAccounts -IBroker -IDataProvider -IMarket -ITrader -IStocks -I.

VPATH = Accounts:Broker:DataProvider:Market:Trader:Stocks

CFLAGS = -fPIC -Wall -std=c++11 $(INC)
CXXFLAGS = $(CFLAGS)

all : $(LIBRARYNAME)

libPlatform.so: $(OBJS)
	$(LINK) -o $@ -shared $^

clean:
	-rm -rf *.d *.o $(LIBRARYNAME)
