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
#include <unistd.h>
#include <stdlib.h>
#include <signal.h> 
//Pour semaphores et memoires partagees
#include <sys/shm.h>
#include <sys/sem.h>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Feu.h"
#include "Mere.h"
#include "/share/public/tp/tp-multitache/Outils.h"
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
static const int TEMPS_ORANGE = 3;
static const int TEMPS_ROUGE = 2;
//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static int monIdDureeFeu;
static int monIdCouleurFeu;
static int monIdSemFeu;

static DureeFeux* maMemDureeFeu;
static CouleurFeux* maMemCouleurFeu;

static unsigned int tempsNS;
static unsigned int tempsEO;

//Pour la gestion des jetons du semaphore de protection de la zone memoire
static struct sembuf reserver = {0, -1, 0};
static struct sembuf liberer = {0, 1, 0};

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
		//Detachement de la memoire
		shmdt(maMemDureeFeu);
		shmdt(maMemCouleurFeu);
		exit(0);
	}
} //----- fin de FinFeu

static void initialisation (void)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	// Attachement des zones de memoires partagees
	maMemCouleurFeu = (CouleurFeux*) shmat(monIdCouleurFeu, NULL, 0);
	maMemDureeFeu = (DureeFeux*) shmat(monIdDureeFeu, NULL, 0);

	// Initialisation des durees des feux
	semop(monIdSemFeu, &reserver, 1);
	tempsEO = maMemDureeFeu->dureeEO;
	tempsNS = maMemDureeFeu->dureeNS;
	semop(monIdSemFeu, &liberer, 1);

	// Les feux de l axe Nord Sud se mettent au vert
	maMemCouleurFeu->couleurNS = true;

	// Affichage des couleurs de depart
	Afficher(COULEUR_AXE_NS, "Vert\0", GRAS, INVERSE);
	Afficher(COULEUR_AXE_EO, "Rouge\0", GRAS, INVERSE);

	// Affichage des temps de depart
	Afficher(TEMPS_AXE_NS, tempsNS, STANDARD, NORMALE);
	Afficher(TEMPS_AXE_EO, tempsNS + TEMPS_ORANGE+TEMPS_ROUGE, STANDARD, NORMALE);

	// Affichage des durées initiales
	Afficher(DUREE_AXE_NS, tempsNS, STANDARD, NORMALE);
	Afficher(DUREE_AXE_EO, tempsEO, STANDARD, NORMALE);
}
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void CreerEtActiverFeu (int unIdDureeFeu, int unIdCouleurFeu, int unIdSemFeu)
// Algorithme :
//
{
	//Creation d'un handler pour SIGUSR2
	struct sigaction action;
	action.sa_handler = FinFeu;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( SIGUSR2, &action, NULL );

/* ----------------------------- Initialisation ------------------------ */
	monIdDureeFeu = unIdDureeFeu;
	monIdCouleurFeu = unIdCouleurFeu;
	monIdSemFeu = unIdSemFeu;
	
	

	initialisation();

/* -------------------------------- Moteur ----------------------------- */
	for(;;)
	{
		
/*----------------------- MISE A JOUR DES DONNEES -----------------------*/
		semop(monIdSemFeu, &reserver, 1);
		tempsEO = maMemDureeFeu->dureeEO;
		tempsNS = maMemDureeFeu->dureeNS;
		semop(monIdSemFeu, &liberer, 1);
		
		Afficher(DUREE_AXE_NS, tempsNS, STANDARD, NORMALE);
		Afficher(DUREE_AXE_EO, tempsEO, STANDARD, NORMALE);

/*--------------------------- FEU NORD SUD -------------------------------*/		
		//FEU NORD SUD VERT
		Afficher(COULEUR_AXE_NS,"Vert  \0", GRAS, NORMALE);
		semop(monIdSemFeu, &reserver, 1);
		maMemCouleurFeu->couleurNS = true;
		semop(monIdSemFeu, &liberer, 1);
		for(int i = tempsNS ; i > 0 ; i--)
		{
			Afficher(TEMPS_AXE_NS, i, STANDARD, NORMALE);
			Afficher(TEMPS_AXE_EO, i + TEMPS_ORANGE+TEMPS_ROUGE, STANDARD, NORMALE);
			sleep(1);
		}

		//FEU NORD SUD ORANGE
		Afficher(COULEUR_AXE_NS,"Orange\0", GRAS, INVERSE);
		semop(monIdSemFeu, &reserver, 1);
		maMemCouleurFeu->couleurNS = false;
		semop(monIdSemFeu, &liberer, 1);
		for(int i = 3 ; i > 0 ; i--)
		{
			Afficher(TEMPS_AXE_NS, i, STANDARD, NORMALE);
			Afficher(TEMPS_AXE_EO, i + TEMPS_ROUGE, STANDARD, NORMALE);
			sleep(1);
		}

		//FEU NORD SUD ROUGE
		Afficher(COULEUR_AXE_NS,"Rouge \0", GRAS, INVERSE);
		for(int i = 2 ; i > 0 ; i--)
		{
			Afficher(TEMPS_AXE_NS, i, STANDARD, NORMALE);
			Afficher(TEMPS_AXE_EO, i, STANDARD, NORMALE);
			sleep(1);
		}
		
/*----------------------- MISE A JOUR DES DONNEES -----------------------*/
		semop(monIdSemFeu, &reserver, 1);
		tempsEO = maMemDureeFeu->dureeEO;
		tempsNS = maMemDureeFeu->dureeNS;
		semop(monIdSemFeu, &liberer, 1);
		
		Afficher(DUREE_AXE_NS, tempsNS, STANDARD, NORMALE);
		Afficher(DUREE_AXE_EO, tempsEO, STANDARD, NORMALE);
		
/*-------------------------- FEU EST OUEST ------------------------------*/
		//FEU EST OUEST VERT
		semop(monIdSemFeu, &reserver, 1);
		maMemCouleurFeu->couleurEO = true;
		semop(monIdSemFeu, &liberer, 1);

		Afficher(COULEUR_AXE_EO,"Vert  \0", GRAS, NORMALE);
		for(int i = tempsEO ; i > 0 ; i--)
		{
			Afficher(TEMPS_AXE_EO, i, STANDARD, NORMALE);
			Afficher(TEMPS_AXE_NS, i + TEMPS_ORANGE+TEMPS_ROUGE, STANDARD, NORMALE);
			sleep(1);
		}

		//FEU EST OUEST ORANGE
		Afficher(COULEUR_AXE_EO,"Orange\0", GRAS, INVERSE);
		semop(monIdSemFeu, &reserver, 1);
		maMemCouleurFeu->couleurEO = false;
		semop(monIdSemFeu, &liberer, 1);
		for(int i = 3 ; i > 0 ; i--)
		{
			Afficher(TEMPS_AXE_EO, i, STANDARD, NORMALE);
			Afficher(TEMPS_AXE_NS, i + TEMPS_ROUGE, STANDARD, NORMALE);
			sleep(1);
		}

		//FEU EST OUEST ROUGE
		Afficher(COULEUR_AXE_EO,"Rouge \0", GRAS, INVERSE);
		for(int i = 2 ; i > 0 ; i--)
		{
			Afficher(TEMPS_AXE_EO, i, STANDARD, NORMALE);
			Afficher(TEMPS_AXE_NS, i, STANDARD, NORMALE);
			sleep(1);
		}
	}



} //----- fin de CreerEtActiverFeu
