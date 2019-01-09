# Simple Makefile to build the example ProgramTrader

LIBNAME = Platform
INSTALLDIR = ../delivery
INCLUDE = -I$(INSTALLDIR)/include
LIBRARY = -L$(INSTALLDIR)/lib -l$(LIBNAME)

CXXFLAGS = -Wall -std=c++11

all: ProgramTrader

ProgramTrader: ProgramTrader.cpp
	g++ -o $@ $^ $(CXXFLAGS) $(INCLUDE) $(LIBRARY)
	@echo "Remember to set:"
	@echo "export LD_LIBRARY_PATH=$(INSTALLDIR)/lib"

clean:
	@rm -rf ProgramTrader *.o *.d
