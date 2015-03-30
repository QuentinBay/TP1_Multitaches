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
#include <unistd.h>
#include <sys/wait.h>
//#include <stdlib.h>
#include <iostream>
#include <signal.h> 

//Pour les IPCs
#include <sys/types.h>
#include <sys/ipc.h>
//Pour memoires partagees
#include <sys/shm.h>
//Pour semaphores
#include <sys/sem.h>
//Pour boites aux lettres
#include <sys/msg.h>

//------------------------------------------------------ Include personnel
#include "Mere.h"
#include "Voie.h"
#include "Feu.h"
#include "GestionClavier.h"
#include "/share/public/tp/tp-multitache/Outils.h"
#include "/share/public/tp/tp-multitache/Menu.h"
#include "/share/public/tp/tp-multitache/Heure.h"
#include "/share/public/tp/tp-multitache/Generateur.h"


using namespace std;

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static void Masquer ( int noSignal )
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
{	
	//On masque SIGUSR2
	struct sigaction action;
	action.sa_handler = SIG_IGN;
	sigemptyset ( &action.sa_mask );
	action.sa_flags = 0;
	sigaction ( SIGUSR2, &action, NULL );
	sigaction ( SIGCHLD, &action, NULL );
	
	InitialiserApplication ( XTERM );

/* ------------------ Creation des memoires partagees ------------------ */
	int idCouleurFeu = shmget (IPC_PRIVATE , sizeof(CouleurFeux), 
														0660 | IPC_CREAT );

	int idDureeFeu = shmget (IPC_PRIVATE, sizeof(DureeFeux), 
														0660 | IPC_CREAT );

	//Semaphores d exclusion mutuelle
	int idSemFeu = semget ( IPC_PRIVATE , 2 , 0660 | IPC_CREAT );

	//Boite aux lettres
	key_t clefBoiteLettres = ftok ("Carrefour",1);
	int boiteLettres = msgget( clefBoiteLettres , IPC_CREAT | 0660 );

/* ---------------- Initialisation des memoires partagees -------------- */
	// Initialisation de CouleurFeux
	CouleurFeux* memCouleurFeux = (CouleurFeux*) shmat(idCouleurFeu, NULL, 0);
	memCouleurFeux->couleurNS = false;
	memCouleurFeux->couleurEO = false;
	shmdt(memCouleurFeux);

	// Initialisation de DureeFeux
	DureeFeux* memDureeFeux = (DureeFeux*) shmat(idDureeFeu, NULL, 0);
	memDureeFeux->dureeEO = 12;
	memDureeFeux->dureeNS = 18;
	shmdt(memDureeFeux);
/* ----------------------- Creation des processus ---------------------- */
	pid_t heure;
	pid_t generateur;
	pid_t voie;
	pid_t feu;
	pid_t gestionClavier;

	if ( (heure = CreerEtActiverHeure()) == 0 )
	{
		/* code fils heure */
	}
	else if ( (generateur = CreerEtActiverGenerateur( 0 , boiteLettres )) == 0 )
	{
		/* code fils generateur */
	}
	else if ( (voie = fork()) == 0 )
	{
		/* code fils voie */
		CreerEtActiverVoie();
	}
	else if ( (feu = fork()) == 0 )
	{
		/* code fils feu */
		CreerEtActiverFeu(idDureeFeu, idCouleurFeu, idSemFeu);
	}
	else if ( (gestionClavier = fork()) == 0 )
	{
		/* code fils gestionClavier */
		CreerEtActiverGestionClavier(generateur, boiteLettres, idDureeFeu, idSemFeu);
	}
	else
	{
		/* code Pere */
		waitpid(gestionClavier, NULL, 0);

/* --------------------- Destruction des processus ---------------------- */		
		kill(generateur, SIGCONT); //On doit envoyer SIGCONT pour le detruire
		kill(generateur, SIGUSR2);
		waitpid(generateur, NULL, 0);

		kill(voie, SIGUSR2);
		waitpid(voie, NULL, 0);

		kill(feu, SIGUSR2);
		waitpid(feu, NULL, 0);

		kill(heure, SIGUSR2);
		waitpid(heure, NULL, 0);
		

		TerminerApplication ( true );
		cout << "destruction de l'appli !\r\n";

/* ---------------- Destruction des memoires partagees ------------------ */
		cout << "destruction des semaphores, mémoires, et boiteLettres !\r\n";
		shmctl ( idCouleurFeu , IPC_RMID , 0 );
		shmctl ( idDureeFeu , IPC_RMID , 0 );
		semctl ( idSemFeu , 2 , IPC_RMID , 0 );
		msgctl ( boiteLettres , IPC_RMID , 0 );
	}
	return 0;
} //----- fin de Nom
