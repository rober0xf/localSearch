CXX = clang++
CXXFLAGS = -Wall -std=c++17 -I/usr/local/include  
LDFLAGS = -lpugixml
SRC = src/main.cpp
OBJ = build/main.o
EXE = build/program

all: $(EXE)

build/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

$(EXE): build/main.o 
	$(CXX) build/main.o -o $(EXE) $(LDFLAGS)

clean:
	rm -f build/*.o build/program 

run: $(EXE)
	./$(EXE)
