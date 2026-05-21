all: 
	mkdir -p bin
	g++ src/*.cpp test/funcional/*.cpp -o bin/funcional_tests

run: all
	./bin/funcional_tests

clean:
	rm -f bin/funcional_tests