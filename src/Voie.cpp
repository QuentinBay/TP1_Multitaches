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
#include <vector>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
//------------------------------------------------------ Include personnel
#include "Voie.h"
#include "Mere.h"
#include "/share/public/tp/tp-multitache/Outils.h"
#include "/share/public/tp/tp-multitache/Voiture.h"	

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static TypeVoie voie;
//memoire partagee pour la couleur des feux
static CouleurFeux* maMemCouleurFeux;
int idMemCouleurFeux;
int idBal;

//Liste des voitures qui sont presentes sur le carrefour
static std::vector<pid_t> voituresCrees;

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
		/*Supprimons toutes les voitures encore presentes sur le carrefour*/
		std::vector<pid_t> ::iterator it;
		for (it=voituresCrees.begin(); it!=voituresCrees.end(); ++it)
		{
			/* Envoie du signal de fin aux voitures */
			kill(*it, SIGUSR2);
			waitpid(*it, NULL, 0);
		}

		//Detachement de la memoire
		shmdt(maMemCouleurFeux);

		exit(0);
	}
	else if ( noSignal == SIGCHLD)
	{
		/* Une voiture a quitte le carrefour */
		//On recupere le pid de cette voiture
		int etat;
		pid_t pidVoiture = wait (&etat);
		std::vector<pid_t> ::iterator it;
		for (it=voituresCrees.begin(); *it!=pidVoiture; ++it)
		{
			voituresCrees.erase(it);
		}
	}
} //----- fin de FinVoie

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverVoie ( TypeVoie uneVoie, int unIdMemCouleurFeux, int unIdBal )
// Algorithme :
//
{
	//Creation d'un handler pour SIGUSR2
	struct sigaction terminerVoie;
	terminerVoie.sa_handler = FinVoie;
	sigemptyset ( &terminerVoie.sa_mask );
	terminerVoie.sa_flags = 0;
	sigaction ( SIGUSR2, &terminerVoie, NULL );

	//Creation d'un handler pour SIGCHLD
	struct sigaction finVoiture;
	finVoiture.sa_handler = FinVoie;
	sigemptyset ( &finVoiture.sa_mask );
	finVoiture.sa_flags = 0;
	sigaction ( SIGCHLD, &finVoiture, NULL );
/* ----------------------------- Initialisation ------------------------ */
	voie = uneVoie;
	idMemCouleurFeux = unIdMemCouleurFeux;
	idBal = unIdBal;

/* -------------------------------- Moteur ----------------------------- */
	for(;;)
	{

	}
} //----- fin de CreerEtActiverVoie

