# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).

# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
OPTIONS = -g -O0 -Wall
CC = g++
#OPTIONS = -O2 -Wall

OBJECTS_ENTITE = date.o magasin.o pointst.o unite.o commande.o
OBJECTS_SERVICE = gestionnaire.o inventaire.o
OBJECTS = $(OBJECTS_ENTITE) $(OBJECTS_SERVICE)

#----------Chemins------------

#Chemins -> testes
test_folder = ./testes
test_avl = $(test_folder)/teste_arbreavl.cpp
test_map = $(test_folder)/teste_arbremap.cpp
test_date = $(test_folder)/teste_date.cpp

#Chemins -> executables
path_objects_folder = ./objects

#Chemins -> structures 
path_structure = ./structure
arbreavl.h = $(path_structure)/arbreavl.h
arbremap.h =  $(path_structure)/arbremap.h
pile.h =  $(path_structure)/pile.h

#Chemins -> service inventaire 
path_service = ./service
path_inventaire =  $(path_service)/inventaire
path_gestionnaire =  $(path_service)/gestionnaire

inventaire.h = $(path_inventaire)/inventaire.h
inventaire.cpp = $(path_inventaire)/inventaire.cpp
inventaire.o = $(path_objects_folder)/inventaire.o

gestionnaire.h = $(path_gestionnaire)/gestionnaire.h
gestionnaire.cpp = $(path_gestionnaire)/gestionnaire.cpp
gestionnaire.o = $(path_objects_folder)/gestionnaire.o


#Chemins -> Repertores des entites
path_entite = ./entite
path_date = $(path_entite)/date
path_point = $(path_entite)/point
path_magasin = $(path_entite)/magasin
path_unite = $(path_entite)/unite

date.cpp = $(path_date)/date.cpp
date.h = $(path_date)/date.h
date.o = $(path_objects_folder)/date.o

pointst.cpp = $(path_point)/pointst.cpp
pointst.h = $(path_point)/pointst.h
pointst.o = $(path_objects_folder)/pointst.o

magasin.o = $(path_objects_folder)/magasin.o
magasin.h = $(path_magasin)/magasin.h
magasin.cpp = $(path_magasin)/magasin.cpp

unite.o = $(path_objects_folder)/unite.o
unite.h = $(path_unite)/unite.h
unite.cpp = $(path_unite)/unite.cpp

commande.o = $(path_objects_folder)/commande.o
commande.cpp = commande.cpp
commande.h = commande.h

all : run

object_folder : 
	mkdir -p objects

compile : object_folder $(OBJECTS)

run : compile
	$(CC) ${OPTIONS} tp2.cpp ./$(path_objects_folder)/* -o tp2 

gestionnaire.o : $(gestionnaire.cpp) $(gestionnaire.h)
	$(CC) ${OPTIONS} -c -o $(gestionnaire.o) $<

pointst.o : $(pointst.cpp) $(pointst.h)
	$(CC) ${OPTIONS} -c -o $(pointst.o) $<

magasin.o : $(magasin.cpp) $(magasin.h)
	$(CC) ${OPTIONS} -c -o $(magasin.o) $<

date.o : $(date.cpp) $(date.h)
	$(CC) ${OPTIONS} -c -o $(date.o) $<

inventaire.o : $(inventaire.cpp) $(inventaire.h) $(unite.o) $(magasin.o) $(arbreavl.h)
	$(CC) ${OPTIONS} -c -o $(inventaire.o) $<

commande.o : $(commande.cpp) $(commande.h)
	$(CC) ${OPTIONS} -c -o $(commande.o) $<

unite.o : $(unite.cpp) $(unite.h)
	$(CC) ${OPTIONS} -c -o $(unite.o) $<

testDATE : $(test_date) $(date.o)
	$(CC) $(OPTIONS) -o testDATE $^

testAVL : $(test_avl) $(arbreavl.h)
	$(CC) $(OPTIONS) -o testAVL $<

testMAP : $(test_map) $(arbreavl.h) $(arbremap.h)
	$(CC) $(OPTIONS) -o testMAP $<

clean:
	rm -rf tp2 *~ *.o
	rm -rf $(path_objects_folder)/*.o
