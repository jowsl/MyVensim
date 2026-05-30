all: functional unit

# Complile and link functional tests and unit tests
functional:
	mkdir -p bin
	g++ src/*.cpp test/functional/*.cpp -o bin/functional_tests

unit:
	mkdir -p bin
	g++ src/*.cpp test/unit/*.cpp -o bin/unit_tests

run-func: functional
	./bin/functional_tests

run-unit: unit
	./bin/unit_tests

clean:
	rm -f bin/functional_tests bin/unit_tests