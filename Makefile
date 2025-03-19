CXX = clang++
CXXFLAGS = -Wall -std=c++17 -I/usr/local/include  -I./include
LDFLAGS = -lpugixml
SRC = src/main.cpp src/lexer.cpp
OBJ = build/main.o build/lexer.o
EXE = build/program

all: $(EXE)

build/main.o: src/main.cpp include/lexer.hpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

build/lexer.o: src/lexer.cpp include/lexer.hpp
	$(CXX) $(CXXFLAGS) -c src/lexer.cpp -o build/lexer.o

$(EXE): $(OBJ) 
	$(CXX) $(OBJ) -o $(EXE) $(LDFLAGS)

clean:
	rm -f build/*.o build/program 

run: $(EXE)
	./$(EXE)
