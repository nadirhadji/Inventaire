# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).


# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall

OBJECTS = date.o epicerie.o pointst.o operation.o

test_folder = ./testes
test_avl = $(test_folder)/teste_arbreavl.cpp
test_map = $(test_folder)/teste_arbremap.cpp
test_date = $(test_folder)/teste_date.cpp

path_exec_folder = ./exec/

path_gestionnaire = ./gestionnaire
gestionnaire.h = $(path_gestionnaire)/gestionnaire.h
gestionnaire.cpp = $(path_gestionnaire)/gestionnaire.cpp
gestionnaire.o = $(path_gestionnaire)/gestionnaire.o

path_structure = ./structure
arbreavl.h = $(path_structure)/arbreavl.h
arbremap.h =  $(path_structure)/arbremap.h
pile.h =  $(path_structure)/pile.h

path_entite = ./entite

path_date = $(path_entite)/date
date.cpp = $(path_date)/date.cpp
date.h = $(path_date)/date.h
date.o = $(path_date)/date.o

path_point = $(path_entite)/point
pointst.cpp = $(path_point)/pointst.cpp
pointst.h = $(path_point)/pointst.h
pointst.o = $(path_point)/pointst.o

all : tp2

tp2 : tp2.cpp $(OBJECTS)
	g++ ${OPTIONS} -o tp2 tp2.cpp $(date.o) epicerie.o $(gestionnaire.o) $(pointst.o)

operation.o : $(gestionnaire.cpp) $(gestionnaire.h)
	g++ ${OPTIONS} -c -o $(gestionnaire.o) $<

pointst.o : $(pointst.cpp) $(pointst.h)
	g++ ${OPTIONS} -c -o $(pointst.o) $<

date.o : $(date.cpp) $(date.h)
	g++ ${OPTIONS} -c -o $(date.o) $<

epicerie.o : epicerie.cpp epicerie.h $(pointst.h) $(arbreavl.h)
	g++ ${OPTIONS} -c -o epicerie.o epicerie.cpp

testDATE : $(test_date) $(date.o)
	g++ $(OPTIONS) -o testDATE $^
	mv ./testDATE $(path_exec_folder)

testAVL : $(test_avl) $(arbreavl.h)
	g++ $(OPTIONS) -o testAVL $<
	mv ./testAVL $(path_exec_folder)

testMAP : $(test_map) $(arbreavl.h) $(arbremap.h)
	g++ $(OPTIONS) -o testMAP $<
	mv ./testMAP $(path_exec_folder)

clean:
	rm -rf tp2 *~ *.o
	rm -rf $(path_date)/*.o
	rm -rf $(path_point)/*.o
	rm -rf $(path_gestionnaire)/*.o
	rm -rf $(path_exec_folder)/*
	

