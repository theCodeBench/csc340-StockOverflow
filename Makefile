# Top level Makefile to do high level things:
# 
# Build and run tests
# Build and package platform for delivery
#

all: package tests

run_tests:
	cd tests ; make ; main
	cd qa_tests ; make ; main

tests:
	cd tests ; make ; main ; make clean

package:
	cd src ; make
	mkdir -p delivery/include delivery/data delivery/lib delivery/ACCOUNTS_DIR
	cp src/*/*.h src/*.h delivery/include
	cp src/libPlatform.so delivery/lib
	cp StockFile.txt delivery/data
	tar cvf Platform.tar delivery Examples

clean:
	cd tests ; make clean
	cd qa_tests ; make clean
	cd src ; make clean
	rm -rf delivery
