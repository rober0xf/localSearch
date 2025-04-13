CXX = clang++
CXXFLAGS = -Wall -std=c++17 -I/usr/local/include  -I./include
LDFLAGS = -lpugixml
SRC = src/main.cpp src/lexer.cpp src/xml_parser.cpp src/document_processor.cpp src/json_writter.cpp
OBJ = build/main.o build/lexer.o build/xml_parser.o build/document_processor.o build/json_writter.o
EXE = build/program

all: $(EXE)

build/main.o: src/main.cpp include/lexer.hpp | build
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o

build/lexer.o: src/lexer.cpp include/lexer.hpp
	$(CXX) $(CXXFLAGS) -c src/lexer.cpp -o build/lexer.o

build/xml_parser.o: src/xml_parser.cpp include/xml_parser.hpp
	$(CXX) $(CXXFLAGS) -c src/xml_parser.cpp -o build/xml_parser.o

build/document_processor.o: src/document_processor.cpp include/document_processor.hpp
	$(CXX) $(CXXFLAGS) -c src/document_processor.cpp -o build/document_processor.o

build/json_writter.o: src/json_writter.cpp include/json_writter.hpp
	$(CXX) $(CXXFLAGS) -c src/json_writter.cpp -o build/json_writter.o

$(EXE): $(OBJ) 
	$(CXX) $(OBJ) -o $(EXE) $(LDFLAGS)

clean:
	rm -f build/*.o build/program 

run: $(EXE)
	./$(EXE)
