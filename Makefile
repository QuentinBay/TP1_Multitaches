# Utilise make pour compiler
EXE             = Carrefour

# Compilateur et editeur de lien
CXX            = g++

# Options de compilation et editions de liens
LIBS = -lncurses -ltcl -ltp
CPPFLAGS        = -Wall -ansi -ggdb -g -std=c++11 -I/share/public/tp/tp-multitache
EDLFLAGS        = -L/share/public/tp/tp-multitache $(LIBS)

#Fichiers
SRC             = src/$(wildcard *.cpp)
INT             = src/Mere.h          #Mettre les .h ici
REAL            = $(INT:.h=.cpp)
OBJ             = $(INT:.h=.o)        #Mettre le .o du programme de test la où ya le main

#Autres commandes et message
ECHO            = @echo
RM              = @rm
BACKUP 		= /share/public/tp/tp-multitache/Compte-Rendu/2015/4/B3434
MESSAGE         = "Succès !!"

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $^ $(EDLFLAGS)
	$(ECHO) $(MESSAGE)


#Mettre les dependances particulieres ici
src/%.o: %.cpp
	$(CXX) -c $< $(CPPFLAGS)

#Supprimer les fichiers
.PHONY: clean backup

clean:
	$(RM) -fv src/*.o

#Sauvegarde d une version backup
backup:
	$(ECHO) "Sauvegarde du backup..."
	cp Makefile $(BACKUP)
	cp src/*.h $(BACKUP)/src
	cp src/*.cpp $(BACKUP)/src
	$(ECHO) "Sauvegarde terminée"
	

