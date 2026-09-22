CXX = g++
CXXFLAGS = -Wall -std=c++20

SRCFILE = src
OUTFILE = output


all: UTTrade

UTTrade: $(OUTFILE)/Request.o $(OUTFILE)/Stock.o $(OUTFILE)/Company.o $(OUTFILE)/Stockholder.o $(OUTFILE)/System.o $(OUTFILE)/main.o
	$(CXX) $^ -o UTTrade

$(OUTFILE)/Request.o:$(SRCFILE)/Request.cpp $(SRCFILE)/Request.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCFILE)/Request.cpp -o $(OUTFILE)/Request.o

$(OUTFILE)/Stock.o: $(SRCFILE)/Stock.cpp $(SRCFILE)/Stock.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCFILE)/Stock.cpp -o $(OUTFILE)/Stock.o

$(OUTFILE)/Company.o: $(SRCFILE)/Company.cpp $(SRCFILE)/Company.hpp $(SRCFILE)/Request.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCFILE)/Company.cpp -o $(OUTFILE)/Company.o

$(OUTFILE)/Stockholder.o: $(SRCFILE)/Stockholder.cpp $(SRCFILE)/Company.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCFILE)/Stockholder.cpp -o $(OUTFILE)/Stockholder.o

$(OUTFILE)/System.o: $(SRCFILE)/System.cpp $(SRCFILE)/Company.hpp $(SRCFILE)/Stockholder.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCFILE)/System.cpp -o $(OUTFILE)/System.o

$(OUTFILE)/main.o: $(SRCFILE)/main.cpp $(SRCFILE)/main.hpp $(SRCFILE)/Request.hpp $(SRCFILE)/Stockholder.hpp $(SRCFILE)/System.hpp $(SRCFILE)/Company.hpp $(SRCFILE)/Stock.hpp
	$(CXX) $(CXXFLAGS) -c $(SRCFILE)/main.cpp -o $(OUTFILE)/main.o

