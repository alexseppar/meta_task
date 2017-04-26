CXX_OPT = -std=c++11 ${ADD}

all: prime bernoulli

prime: prime.o prime_meta.o
	$(CXX) prime.o prime_meta.o $(CXX_OPT) -o prime
prime.o: prime.cpp
	$(CXX) -c $(CXX_OPT) prime.cpp
prime_meta.o: prime_meta.cpp
	$(CXX) -c $(CXX_OPT) prime_meta.cpp
	
bernoulli: bern.o
	$(CXX) bern.o $(CXX_OPT) -o bern
bern.o: bern.cpp
	$(CXX) -c $(CXX_OPT) bern.cpp
	
clean:
	rm -rf *.o
