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
#include "Voie.h"
#include "GestionClavier.h"
#include "/share/public/tp/tp-multitache/Outils.h"
#include "/share/public/tp/tp-multitache/Menu.h"
#include "/share/public/tp/tp-multitache/Heure.h"

#include <unistd.h>
#include <sys/wait.h>
//#include <stdlib.h>
//#include <iostream>
//#include <signal.h> 


using namespace std;

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
	
	InitialiserApplication ( XTERM );
	pid_t heure;
	pid_t gestionMenu;

	if ( (heure=CreerEtActiverHeure()) == 0)
	{
		/* code fils heure */
	}
	else if ( (gestionMenu=fork()) == 0 )
	{
		/* code fils gestionMenu */
		Menu();
		//Commande ('q');
	}
	else
	{
		/* code Pere */
		waitpid(gestionMenu, NULL, 0);
		kill(heure, SIGUSR2);
		TerminerApplication ( true );
		//exit(0);
	}
	//sleep(10);
	//TerminerApplication ( true );
	return 0;
} //----- fin de Nom
