#Executable
EXE             = Carrefour
# Compilateur et editeur de lien
CXX            = g++

# Librairies et drapeaux
LIBS = -ltp -lncurses -ltcl 
CPPFLAGS        = -Wall -ansi -ggdb -g -std=c++11 -I/share/public/tp/tp-multitache
EDLFLAGS        = -L/share/public/tp/tp-multitache $(LIBS)

#Fichiers sources
SRC             =  
INT             = src/Mere.h src/Voie.h src/Feu.h src/GestionClavier.h       #Mettre les .h ici
REAL            = $(INT:.h=.cpp)
OBJ             = $(INT:.h=.o)      

#Affichage, sauvegarde et suppression
ECHO            = @echo
RM              = @rm
BACKUP 		= /share/public/tp/tp-multitache/Compte-Rendu/2015/4/B3434/TP-Multitache
MESSAGE         = "Succès !!"

$(EXE): $(OBJ)
	$(CXX) -o $(EXE) $^ $(EDLFLAGS)
	$(ECHO) $(MESSAGE)


#Creation des .o
src/%.o: %.cpp 
	$(CXX) -c $< $(CPPFLAGS)


#Eviter fichiers de meme nom
.PHONY: clean backup

#Supprimer les fichiers .o
clean:
	$(RM) -fv src/*.o

#Sauvegarde d une version backup
backup:
	cp Makefile $(BACKUP)
	cp src/*.h $(BACKUP)/src
	cp src/*.cpp $(BACKUP)/src
	$(ECHO) "Sauvegarde terminée"
	

