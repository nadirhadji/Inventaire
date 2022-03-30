# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).

# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
OPTIONS = -g -O0 -Wall -std=c++11
CC = g++
#OPTIONS = -O2 -Wall -std=c++11

OBJECTS_ENTITE = date.o pointst.o unite.o magasin.o panier.o commande.o
OBJECTS_SERVICE = data.o recommandation.o gestionnaire.o
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

#Chemins -> Repertoire des services 
path_service = ./service

path_data =  $(path_service)/data
path_gestionnaire =  $(path_service)/gestionnaire
path_recommandation = $(path_service)/recommandation

data.h = $(path_data)/data.h
data.cpp = $(path_data)/data.cpp
data.o = $(path_objects_folder)/data.o

gestionnaire.h = $(path_gestionnaire)/gestionnaire.h
gestionnaire.cpp = $(path_gestionnaire)/gestionnaire.cpp
gestionnaire.o = $(path_objects_folder)/gestionnaire.o

recommandation.h = $(path_recommandation)/recommandation.h
recommandation.cpp = $(path_recommandation)/recommandation.cpp
recommandation.o = $(path_objects_folder)/recommandation.o

#Chemins -> Repertoires des entites
path_entite = ./entite

path_commande = $(path_entite)/commande
path_date = $(path_entite)/date
path_magasin = $(path_entite)/magasin
path_panier = $(path_entite)/panier
path_point = $(path_entite)/point
path_unite = $(path_entite)/unite

commande.cpp = $(path_commande)/commande.cpp
commande.h = $(path_commande)/commande.h
commande.o = $(path_objects_folder)/commande.o

date.cpp = $(path_date)/date.cpp
date.h = $(path_date)/date.h
date.o = $(path_objects_folder)/date.o

magasin.cpp = $(path_magasin)/magasin.cpp
magasin.h = $(path_magasin)/magasin.h
magasin.o = $(path_objects_folder)/magasin.o

panier.cpp = $(path_panier)/panier.cpp
panier.h = $(path_panier)/panier.h
panier.o = $(path_objects_folder)/panier.o

pointst.cpp = $(path_point)/pointst.cpp
pointst.h = $(path_point)/pointst.h
pointst.o = $(path_objects_folder)/pointst.o

unite.cpp = $(path_unite)/unite.cpp
unite.h = $(path_unite)/unite.h
unite.o = $(path_objects_folder)/unite.o

all : run

object_folder : 
	mkdir -p objects

compile : object_folder $(OBJECTS)

run : compile
	$(CC) ${OPTIONS} tp2.cpp ./$(path_objects_folder)/* -o tp2 

pointst.o : $(pointst.cpp) $(pointst.h)
	$(CC) ${OPTIONS} -c -o $(pointst.o) $<

magasin.o : $(magasin.cpp) $(magasin.h)
	$(CC) ${OPTIONS} -c -o $(magasin.o) $<

date.o : $(date.cpp) $(date.h)
	$(CC) ${OPTIONS} -c -o $(date.o) $<

commande.o : $(commande.cpp) $(commande.h)
	$(CC) ${OPTIONS} -c -o $(commande.o) $<

unite.o : $(unite.cpp) $(unite.h)
	$(CC) ${OPTIONS} -c -o $(unite.o) $<

panier.o : $(panier.cpp) $(panier.h)
	$(CC) ${OPTIONS} -c -o $(panier.o) $<

data.o : $(data.cpp) $(data.h) $(unite.h) $(magasin.o) $(arbreavl.h)
	$(CC) ${OPTIONS} -c -o $(data.o) $<

recommandation.o : $(recommandation.cpp) $(recommandation.h)
	$(CC) ${OPTIONS} -c -o $(recommandation.o) $<

gestionnaire.o : $(gestionnaire.cpp) $(gestionnaire.h)
	$(CC) ${OPTIONS} -c -o $(gestionnaire.o) $<

testDATE : $(test_date) $(date.o)
	$(CC) $(OPTIONS) -o testDATE $^

testAVL : $(test_avl) $(arbreavl.h)
	$(CC) $(OPTIONS) -o testAVL $<

testMAP : $(test_map) $(arbreavl.h) $(arbremap.h)
	$(CC) $(OPTIONS) -o testMAP $<

clean:
	rm -rf tp2 *~ *.o
	rm -rf $(path_objects_folder)/*.o
