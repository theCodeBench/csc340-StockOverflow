SOURCE = main.cpp Account.cpp AccountProvider.cpp Broker.cpp Market.cpp DataProvider.cpp\
	 Trader.cpp	TraderHelper.cpp FunctionalTestAccountEmpty.cpp\
	FunctionalTestInvalidTrading.cpp FunctionalTestFeatureTest.cpp\
	RegressionTestLimitBuy.cpp RegressionTestStockData.cpp FunctionalTestLimitBuy.cpp

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Archive
AR = ar rs

# Compiler flags
INC = -IAccounts/ -IMarket/ -IBroker/ -IDataProvider/ \
      -I../src/Accounts/ -I../src/Broker -I../src/Market -I../src/DataProvider \
      -I../src/Trader -I../src/Stocks -I../src
CFLAGS = -fPIC -Wall -std=c++11 $(INC)
CXXFLAGS = $(CFLAGS)
VPATH = ../src/Accounts/:../src/Broker:../src/Market:../src/DataProvider:../src/Trader:../src/Stocks

# Fill in special libraries needed here
LIBS =

.PHONY: clean

# Targets include all, clean, debug, tar

all : main

main: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core main

debug: CXXFLAGS = -DDEBUG -g -std=c++11
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

