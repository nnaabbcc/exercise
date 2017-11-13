
all: if_init_test virtualtest struct_binding_test no_loop

if_init_test: if_init_test.cpp
	g++ -std=c++1z -o if_init_test if_init_test.cpp

virtualtest: virtualtest.cpp
	g++ -std=c++1z -o virtualtest virtualtest.cpp

struct_binding_test: struct_binding_test.cpp
	g++ -std=c++1z -o struct_binding_test struct_binding_test.cpp

no_loop: no_loop.cpp
	g++ -std=c++1z -o $@ $<

clean:
	@rm -f if_init_test
	@rm -f virtualtest
	@rm -f struct_binding_test
	@rm -f no_loop
