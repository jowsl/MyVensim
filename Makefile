all: functional unit

#cria biblioteca dinâmica a partir dos arquivos .cpp
lib/libmyvensim.so: src/*.cpp
	mkdir -p lib
	g++ -fPIC -shared src/*.cpp -o lib/libmyvensim.so

#Compila os testes linkando com a biblioteca dinâmica criada acima
#-L informa onde procurar a biblioteca
#-l informa qual biblioteca linkar

functional: lib/libmyvensim.so
	mkdir -p bin
	g++ test/functional/*.cpp -o bin/functional_tests -L./lib -lmyvensim 

unit: lib/libmyvensim.so
	mkdir -p bin
	g++ test/unit/*.cpp -o bin/unit_tests -L./lib -lmyvensim

#executa os teste, fala pro wsl onde encotnra a biblioteca dinamica
run-func: functional
	LD_LIBRARY_PATH=./lib ./bin/functional_tests

run-unit: unit
	LD_LIBRARY_PATH=./lib ./bin/unit_tests
#faz a limpeza
clean:
	rm -rf bin/* lib/* 