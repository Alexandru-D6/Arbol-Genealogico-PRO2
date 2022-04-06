OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Especie.o Cjt_especie.o Tabla_distancias.o Cjt_cluster.o
	g++ -o program.exe program.o Especie.o Cjt_especie.o Tabla_distancias.o Cjt_cluster.o $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

Especie.o: Especie.cc
	g++ -c Especie.cc $(OPCIONS)

Cjt_especie.o: Cjt_especie.cc
	g++ -c Cjt_especie.cc $(OPCIONS)

Cjt_cluster.o: Cjt_cluster.cc
	g++ -c Cjt_cluster.cc $(OPCIONS)

Tabla_distancias.o: Tabla_distancias.cc
	g++ -c Tabla_distancias.cc $(OPCIONS)

clean:
	rm -f Cjt_cluster.o
	rm -f Cjt_especie.o
	rm -f Especie.o

tar:
	del -f practica.tar
	tar -cvf practica.tar Makefile Especie.cc Especie.hh program.cc Cjt_cluster.cc Cjt_cluster.hh Tabla_distancias.cc Tabla_distancias.hh Cjt_especie.cc Cjt_especie.hh html.zip