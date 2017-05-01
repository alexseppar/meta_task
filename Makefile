CXX_OPT = -std=c++11 ${ADD}

all: compile

bernoulli: bern.o
	$(CXX) bern.o $(CXX_OPT) -o bern
bern.o: bern.cpp
	$(CXX) -c $(CXX_OPT) bern.cpp
	
clean:
	rm -rf *.o
