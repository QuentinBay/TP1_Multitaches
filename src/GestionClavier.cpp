/*************************************************************************
                           GestionClavier  -  description
                             -------------------
    début                : GestionClavier
    copyright            : (C) GestionClavier par GestionClavier
    e-mail               : GestionClavier
*************************************************************************/

//---------- Réalisation de la tâche <GestionClavier> (fichier GestionClavier.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/msg.h>
//Pour semaphores et memoires partagees
#include <sys/shm.h>
#include <sys/sem.h>
using namespace std;
//------------------------------------------------------ Include personnel
#include "GestionClavier.h"
#include "Mere.h"
#include "/share/public/tp/tp-multitache/Menu.h"
#include "/share/public/tp/tp-multitache/Outils.h"
#include "/share/public/tp/tp-multitache/Voiture.h"	
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static pid_t pidGenerateur;
static int idBal;
static int idMemDuree;
static int idSem;
static DureeFeux* memDureeFeux;
static bool Off;
static unsigned int numVoiture = 0;
//Gestion des jetons
static struct sembuf reserver = {0, -1, 0};
static struct sembuf liberer = {0, 1, 0};
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
void CreerEtActiverGestionClavier (pid_t unPidGenerateur, int unIdBal, 
									int unIdMemDuree, int unIdSem)
// Algorithme : Appel Menu
//
{
/* ----------------------------- Initialisation ------------------------ */	
	pidGenerateur = unPidGenerateur;
	idBal = unIdBal;
	idMemDuree = unIdMemDuree;
	idSem = unIdSem;
	Off = false;

	//Attachement de la memoire partagee
	memDureeFeux = (DureeFeux*) shmat(idMemDuree, NULL, 0);

/* -------------------------------- Moteur ----------------------------- */
	Menu();
}

void Commande ( char code )
// Algorithme :
//
{
	if ( code=='Q' )
	{
		/* On quitte l application */
		//Detachement de la memoire partagee
		shmdt(memDureeFeux);

		exit(0);
		
	}
	else
	{
		if ( Off )
		{
			/* Il faut desactiver le generateur */
			kill ( pidGenerateur , SIGSTOP );
			Effacer ( ETAT_GENERATEUR );
			Afficher ( ETAT_GENERATEUR , "OFF" , GRAS );
			Off = false;
			
		}
		else
		{
			/* Il faut activer le generateur */
			kill ( pidGenerateur , SIGCONT );
			Effacer ( ETAT_GENERATEUR );
			Afficher ( ETAT_GENERATEUR , "ON" , GRAS );
			Off = true;
		}
	}
} //----- fin de Commande

void Commande ( TypeVoie uneEntree, TypeVoie uneSortie )
// Algorithme :
//
{
	struct Voiture voiture;
	voiture.entree = uneEntree;
	voiture.sortie = uneSortie;
	if ( numVoiture == numeroMaxManuel )
	{
		/* On a atteint le numero max */
		numVoiture = numeroMinManuel;
	}
	else
	{
		numVoiture++;
	}
	voiture.numero = numVoiture;

	//Creation et envoie du message
	struct MsgVoiture *ptrMsg, msgVoiture;
	ptrMsg=&msgVoiture;
	ptrMsg->type=(long)uneEntree;
	ptrMsg->uneVoiture=voiture;
	

	if ( (msgsnd( idBal, ptrMsg, TAILLE_MSG_VOITURE, 0 )) == 0 )
	{
		Effacer (NUMERO);
		Afficher(NUMERO, voiture.numero, GRAS);
		Effacer (ENTREE);
		Afficher(ENTREE, voiture.entree, GRAS);
		Effacer (SORTIE);
		Afficher(SORTIE, voiture.sortie, GRAS);
		OperationVoie (PLUS, uneEntree);
	}
	//Effacer (MESSAGE);
	//Afficher(MESSAGE, "msg créé !", GRAS);
} //----- fin de Commande

void Commande ( TypeVoie uneVoie, unsigned int duree )
// Algorithme : Prise du jeton, modification de la duree puis le jeton
// est reposé
{
	
	if (uneVoie==NORD || uneVoie==SUD)
	{
		/* On modifie la duree du feu nord-sud */
		semop(idMemDuree, &reserver, 1);
		memDureeFeux->dureeNS = duree;
		semop(idMemDuree, &liberer, 1);
	}
	else if (uneVoie==EST || uneVoie==OUEST)
	{
		/* On modifie la duree du feu est-ouest */
		semop(idMemDuree, &reserver, 1);
		memDureeFeux->dureeEO = duree;
		semop(idMemDuree, &liberer, 1);
	}
	else
	{
		Effacer(MESSAGE);
		Afficher(MESSAGE, "ERREUR : modification de la duree");
	}

} //----- fin de Commande