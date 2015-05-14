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
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
//------------------------------------------------------ Include personnel
#include "errno.h"
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
int idSem;

//Liste des voitures qui sont presentes sur le carrefour
static std::vector<pid_t> voituresCrees;

//Pour la gestion des jetons du semaphore de protection de la zone memoire
static struct sembuf reserver = {0, -1, 0};
static struct sembuf liberer = {0, 1, 0};

static bool etatFeuNS;
static bool etatFeuEO;
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
void CreerEtActiverVoie ( TypeVoie uneVoie, int unIdMemCouleurFeux, int unIdBal, int unIdSem )
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
	idSem = unIdSem;
	struct MsgVoiture message;
	//Attachement de la memoire partagee
	maMemCouleurFeux = (CouleurFeux*) shmat(idMemCouleurFeux, NULL, 0);

/* -------------------------------- Moteur ----------------------------- */
	for(;;)
	{
		//Verification qu il y a une voiture en attente
		int res;
	    do{
	    	res = msgrcv(idBal, &message, TAILLE_MSG_VOITURE, voie, 0);
	    }
	    while (res==-1 && errno==EINTR);
	    

    	Effacer(MESSAGE);
    	Afficher(MESSAGE, voie);
	    // Affichage des voitures en attente au Feu     
	    DessinerVoitureFeu( message.uneVoiture.numero, message.uneVoiture.entree, 
      						message.uneVoiture.sortie);
	    OperationVoie (MOINS, voie);

	    if (voie == NORD || voie == SUD)
	    {
	        /*Verification toutes les secondes de la couleur du feu Nord-Sud*/
	        semop(idSem, &reserver, 1);
			etatFeuNS = maMemCouleurFeux->couleurNS;
			semop(idSem, &liberer, 1);

	        while (!etatFeuNS)
	        {
	            sleep(1);
	            semop(idSem, &reserver, 1);
				etatFeuNS = maMemCouleurFeux->couleurNS;
				semop(idSem, &liberer, 1);
	        }
    
	        //Ajout d une voiture 
	        pid_t voiture =DeplacerVoiture(message.uneVoiture.numero, 
	    										message.uneVoiture.entree, 
	    										message.uneVoiture.sortie);
	        voituresCrees.push_back(voiture);
  		}
	    else if (voie == EST || voie == OUEST)
	    {
	        /*Verification toutes les secondes de la couleur du feu Est-Ouest*/
	        semop(idSem, &reserver, 1);
			etatFeuEO = maMemCouleurFeux->couleurEO;
			semop(idSem, &liberer, 1);

	        while (!etatFeuEO)
	        {
	            sleep(1);
	            semop(idSem, &reserver, 1);
				etatFeuEO = maMemCouleurFeux->couleurEO;
				semop(idSem, &liberer, 1);
	        }

	        //Ajout d une voiture
	        pid_t voiture =DeplacerVoiture(message.uneVoiture.numero, 
	        									message.uneVoiture.entree, 
	        									message.uneVoiture.sortie);
	        voituresCrees.push_back(voiture);
  		}
    	
	}
} //----- fin de CreerEtActiverVoie

