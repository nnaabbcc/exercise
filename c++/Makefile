
all: if_init_test virtualtest

if_init_test: if_init_test.cpp
	g++ -std=c++1z -o if_init_test if_init_test.cpp

virtualtest: virtualtest.cpp
	g++ -std=c++1z -o virtualtest virtualtest.cpp

clean:
	@rm -f if_init_test
	@rm -f virtualtest
