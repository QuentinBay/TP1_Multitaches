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
#include "/share/public/tp/tp-multitache/Generateur.h"

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
	
	InitialiserApplication ( XTERM );

/* ------------------ Creation des memoires partagees ------------------ */
	key_t clefCouleurFeu = ftok ("Carrefour",1);
	int memCouleurFeu = shmget ( clefCouleurFeu , sizeof(int)*4 , 660 | IPC_CREAT );

	key_t clefDureeFeu = ftok ("Carrefour",1);
	int memDureeFeu = shmget ( clefDureeFeu , sizeof(int)*4 , 660 | IPC_CREAT );

	//Semaphores
	key_t clefSemFeu = ftok ("Carrefour",1);
	int semFeu = semget ( clefSemFeu , 2 , 660 | IPC_CREAT );

	//Boite aux lettres
	key_t clefBoiteLettres = ftok ("Carrefour",1);
	int boiteLettres = ( clefBoiteLettres , 660 | IPC_CREAT );

/* ----------------------- Creation des processus ---------------------- */
	pid_t heure;
	pid_t gestionClavier;
	pid_t generateur;
	pid_t voie;

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
	else if ( (gestionClavier = fork()) == 0 )
	{
		/* code fils gestionClavier */
		Menu(); //Appeler creerEtActiverGestionClavier()
	}
	else
	{
		/* code Pere */
		waitpid(gestionClavier, NULL, 0);

/* --------------------- Destruction des processus ---------------------- */		
		kill(generateur, SIGUSR2);
		kill(voie, SIGUSR2);
		kill(heure, SIGUSR2);
		

		TerminerApplication ( true );
		cout << "destruction de l'appli !\r\n";

/* ---------------- Destruction des memoires partagees ------------------ */
		cout << "destruction des semaphores, mémoires, et boiteLettres !\r\n";
		shmctl ( memCouleurFeu , IPC_RMID , 0 );
		shmctl ( memDureeFeu , IPC_RMID , 0 );
		semctl ( semFeu , 2 , IPC_RMID , 0 );
		msgctl ( boiteLettres , IPC_RMID , 0 );
	}
	return 0;
} //----- fin de Nom
