CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = \
	src/system.cpp \
	src/flow.cpp \
	src/model.cpp \
	test/funcional/main.cpp \
	test/funcional/funcional_tests.cpp

TARGET = bin/testes_funcionais

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)