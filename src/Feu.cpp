/*************************************************************************
                           Feu  -  description
                             -------------------
    début                : Feu
    copyright            : (C) Feu par Feu
    e-mail               : Feu
*************************************************************************/

//---------- Réalisation de la tâche <Feu> (fichier Feu.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <stdlib.h>
#include <signal.h> 
//------------------------------------------------------ Include personnel
#include "Feu.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void FinFeu ( int noSignal )
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
} //----- fin de FinFeu

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverFeu ( void )
// Algorithme :
//
{
	//Creation d'un handler pour SIGUSR2
	struct sigaction action;
	action.sa_handler = FinFeu;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( SIGUSR2, &action, NULL );


} //----- fin de CreerEtActiverFeu
