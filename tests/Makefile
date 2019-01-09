SOURCE = main.cpp  \
         TestBrokerAction.cpp TestBrokerCreate.cpp TestBrokerGetInfo.cpp \
         TestDataProviderCreate.cpp TestDataProviderStockInteract.cpp \
         TestBuySellStock.cpp TestGetStockList.cpp TestInitMarket.cpp \
         TestAccountActions.cpp TestAccountCreate.cpp TestAccountProvider.cpp \
         TestTrader.cpp \
         Account.cpp AccountProvider.cpp Broker.cpp Market.cpp \
         DataProvider.cpp Trader.cpp

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Archive
AR = ar rs

# Compiler flags
INC = -IAccounts/ -IMarket/ -IBroker/ -IDataProvider/ -I../src/Accounts/ \
      -I../src/Broker -I../src/Market -I../src/DataProvider -I../src/Trader \
      -I../src/Stocks -I../src
CFLAGS = -fPIC -Wall -std=c++11 $(INC)
CXXFLAGS = $(CFLAGS) 
VPATH = Accounts/:Market/:Broker/:DataProvider/:Trader/:../src/Accounts/:../src/Broker:../src/Market:../src/DataProvider:../src/Trader

# Fill in special libraries needed here
LIBS =

.PHONY: clean

# Targets include all, clean, debug, tar

all : main

main: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core main

debug: CXXFLAGS = -DDEBUG -g -std=c++11 $(INC)
debug: main

tar: clean
	tar zcvf main.tgz $(SOURCE) *.h Makefile

help:
	@echo "	make main  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core testMain"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

