CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: main

clean:
	rm main Product.o Store.o User.o

main: main.cpp Product.o Store.o User.o
	$(CXX) $(CXXFLAGS) main.cpp Product.o Store.o User.o -o main

Product.o: Product.cpp
	$(CXX) $(CXXFLAGS) -c Product.cpp

Store.o: Store.cpp
	$(CXX) $(CXXFLAGS) -c Store.cpp

User.o: User.cpp
	$(CXX) $(CXXFLAGS) -c User.cpp

