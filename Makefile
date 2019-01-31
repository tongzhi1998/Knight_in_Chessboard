CPPFLAGS = g++ -g -Wall -std=c++11 

all:Knight

Knight: Knight_Test.cpp Board.cpp
	 $(CPPFLAGS) $^ $(GTEST_LL) -o $@
	 ./Knight

clean:
	rm Knight