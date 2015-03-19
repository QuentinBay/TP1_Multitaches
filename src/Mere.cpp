/*************************************************************************
                           Mere  -  description
                             -------------------
    début                : Mere
    copyright            : (C) Mere par Mere
    e-mail               : Mere
*************************************************************************/

//---------- Réalisation de la tâche <Mere> (fichier Mere.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "/share/public/tp/tp-multitache/Outils.h"
#include <unistd.h>
#include "/share/public/tp/tp-multitache/Menu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main ( )
// Algorithme :
//
{
	int pid_t noFils;
	InitialiserApplication ( XTERM );
	if ( (noFils=fork())==0 )
		//Code fils
	{
		Menu();
	}
	else
		//code pere
	{
		pid_t ret = waitpid(noFils, NULL, 0);
		TerminerApplication ( true );
		exit(0);
	}
	//sleep(10);
	TerminerApplication ( true );
	return 0;
} //----- fin de Nom
