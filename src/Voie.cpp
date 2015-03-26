/*************************************************************************
                           Voie  -  description
                             -------------------
    début                : Voie
    copyright            : (C) Voie par Voie
    e-mail               : Voie
*************************************************************************/

//---------- Réalisation de la tâche <Voie> (fichier Voie.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h> 
//------------------------------------------------------ Include personnel
#include "Voie.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void FinVoie ( int noSignal )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	if ( noSignal == SIGUSR2 )
	{
		exit(0);
	}
} //----- fin de FinVoie

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverVoie ( void )
// Algorithme :
//
{
	//Creation d'un handler pour SIGUSR2
	struct sigaction action;
	action.sa_handler = FinVoie;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( SIGUSR2, &action, NULL );


} //----- fin de CreerEtActiverVoie

